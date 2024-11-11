// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponItemData_Sword.h"
#include "Kismet/GameplayStatics.h"
#include "../RPGImitationCharacter.h"
#include "GameData/GameCollision.h"

UWeaponItemData_Sword::UWeaponItemData_Sword()
{
	Radius = 200.f;
	WeaponStat.Attack = 10.f;
	WeaponStat.AttackRange = 200.f;
}

void UWeaponItemData_Sword::Attack(int32 damage, float TraceDistance, UParticleSystem* Particle)
{
	Super::Attack(damage, TraceDistance, Particle);

	if (MyOwner)
	{
		TArray<FHitResult> TraceHits;
		FVector TraceStart = MyOwner->GetActorLocation();
		FVector TraceEnd = TraceStart + (MyOwner->GetActorForwardVector() * TraceDistance);
		FCollisionShape SweepShape = FCollisionShape::MakeSphere(Radius);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);

		bool bResult = GetWorld()->SweepMultiByChannel(TraceHits, TraceStart, TraceEnd,
			FQuat::Identity, MELEE_ATTACK, SweepShape, QueryParams);
		if (bResult)
		{
			for (FHitResult& Hit : TraceHits)
			{
				FDamageEvent DamageEvent;
				Hit.Actor->TakeDamage(damage, DamageEvent, MyOwner->GetController(), MyOwner);
				if (Particle)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, Hit.Actor->GetTransform());
				}
			}
		}
	}
}
