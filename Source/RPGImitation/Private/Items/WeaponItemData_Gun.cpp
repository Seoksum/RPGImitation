// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponItemData_Gun.h"
#include "GameData/GameEnums.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "../RPGImitationCharacter.h"
#include "Enemies/Enemy.h"
#include "GameData/GameCollision.h"


UWeaponItemData_Gun::UWeaponItemData_Gun()
{
	WeaponType = EWeaponType::WEAPON_Gun;
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> MuzzleEffectPath(TEXT("ParticleSystem'/Game/Import/WeaponEffects/Muzzle/P_Muzzle_Large.P_Muzzle_Large'"));
	if (MuzzleEffectPath.Succeeded())
	{
		MuzzleEffect = MuzzleEffectPath.Object;
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultImpactEffectPath(TEXT("ParticleSystem'/Game/Import/FXVarietyPack/Particles/P_ky_hit2.P_ky_hit2'"));
	if (DefaultImpactEffectPath.Succeeded())
	{
		DefaultImpactEffect = DefaultImpactEffectPath.Object;
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> BloodImpactEffectPath(TEXT("ParticleSystem'/Game/Import/WeaponEffects/BloodImpact/P_blood_splash_02.P_blood_splash_02'"));
	if (BloodImpactEffectPath.Succeeded())
	{
		BloodImpactEffect = BloodImpactEffectPath.Object;
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> TracerEffectPath(TEXT("ParticleSystem'/Game/Import/WeaponEffects/BasicTracer/P_SmokeTrail.P_SmokeTrail'"));
	if (TracerEffectPath.Succeeded())
	{
		TracerEffect = TracerEffectPath.Object;
	}

	ConstructorHelpers::FObjectFinder<USoundBase> SoundObj(TEXT("SoundWave'/Game/Contents/Sounds/AssaultRifle_Shot05.AssaultRifle_Shot05'"));
	if (SoundObj.Succeeded())
	{
		FireSound = SoundObj.Object;
	}


	MuzzleSocketName = "MuzzleFlashSocket";
	TracerTargetName = "Target";

	BaseDamage = 20.f;
	RateOfFire = 600.f; // 분 당 60개 총알
	TraceDistance = 1000.f;
	TimeBetweenShots = 60.f / RateOfFire;

	WeaponStat.Attack = 15.f;
	WeaponStat.AttackRange = 200.f;
}

void UWeaponItemData_Gun::Attack()
{
	Super::Attack();

	if (MyOwner)
	{
		FHitResult Hit;
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation); // OUT parameter

		FVector TraceStart = MyOwner->GetWeaponMeshSocketLocation(MuzzleSocketName);
		FVector ShotDirection = MyOwner->GetActorRotation().Vector();
		FVector TraceEnd = TraceStart + (ShotDirection * TraceDistance); // 종료 지점
		FVector TraceEndPoint = TraceEnd;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);

		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, RANGED_ATTACK, QueryParams);
		if (bHit)
		{
			AEnemy* Enemy = Cast<AEnemy>(Hit.GetActor());
			TraceEndPoint = Hit.ImpactPoint;
			if (Enemy)
			{
				FDamageEvent DamageEvent;
				Enemy->TakeDamage(BaseDamage, DamageEvent, MyOwner->GetInstigatorController(), MyOwner);
				PlayImpactEffects(TraceEndPoint, BloodImpactEffect);
			}
			else
			{
				PlayImpactEffects(TraceEndPoint, DefaultImpactEffect);
			}
		}

		PlayFireEffects(TraceEndPoint);
		LastFiredTime = World->TimeSeconds; // 마지막 발사 시간을 기록(World의 time)
	}
}

void UWeaponItemData_Gun::StartFire()
{
	float FirstDelay = FMath::Max(LastFiredTime + TimeBetweenShots - World->TimeSeconds, 0.f);
	World->GetTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &UWeaponItemData_Gun::Attack, TimeBetweenShots, true, FirstDelay);
	UGameplayStatics::PlaySoundAtLocation(this, FireSound, MyOwner->GetActorLocation());
}

void UWeaponItemData_Gun::StopFire()
{
	World->GetTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
}

void UWeaponItemData_Gun::PlayFireEffects(FVector TraceEndPoint)
{
	if (MuzzleEffect)
	{
		//UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MyOwner->GetRootComponent(), MuzzleSocketName);
	}

	if (MyOwner)
	{
		if (TracerEffect)
		{
			// TracerEffect는 'P_SmokeTrail'인데 이 파티클시스템을 적용하기 위해서는 Source와 Target 부분이 있다. 
			FVector MuzzleLocation = MyOwner->GetWeaponMeshSocketLocation(MuzzleSocketName);
			UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleLocation);
			if (TracerComp)
			{
				TracerComp->SetVectorParameter("Target", TraceEndPoint); // P_SmokeTrail의 Target에서 Target Name을 찾아 인자로 넣는다.
			}
		}
		//MyOwner->CameraShake(FireCamShake);
	}
}

void UWeaponItemData_Gun::PlayImpactEffects(FVector ImpactPoint, UParticleSystem* Particle)
{
	if (Particle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, ImpactPoint);
	}
}

