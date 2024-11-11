// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponItemData_Bow.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Items/Arrow.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../RPGImitationCharacter.h"

UWeaponItemData_Bow::UWeaponItemData_Bow()
{
	//SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	//RootComponent = MeshComp;
	//static ConstructorHelpers::FClassFinder<ACharacter_Greystone> BP_Greystone1(TEXT("Blueprint'/Game/Blueprints/MainCharacter/Greystone/BP_Greystone.BP_Greystone_C'"));

	static ConstructorHelpers::FClassFinder<AArrow> ArrowClassFinder(TEXT("Blueprint'/Game/Contents/Blueprints/Actors/Weapons/BP_Arrow.BP_Arrow_C'"));
	if (ArrowClassFinder.Succeeded())
	{
		ArrowClass = ArrowClassFinder.Class;
	}

	ConstructorHelpers::FObjectFinder<USoundBase> SoundObj(TEXT("SoundWave'/Game/Contents/Sounds/Arrow+Swoosh+1.Arrow+Swoosh+1'"));
	if (SoundObj.Succeeded())
	{
		ShootSound = SoundObj.Object;
	}

	ArrowSpeedVal = 4000.f;
	WeaponStat.Attack = 15.f;
	WeaponStat.AttackRange = 200.f;
}

void UWeaponItemData_Bow::Attack()
{
	Super::Attack();

	if (MyOwner)
	{
		FVector SpawnLocation = MyOwner->GetWeaponMeshSocketLocation(FName("ArrowSocket"));
		FRotator SpawnRotation = MyOwner->GetActorRotation();
		FTransform SpawnTransform(SpawnRotation, SpawnLocation);
		
		Arrow = GetWorld()->SpawnActorDeferred<AArrow>(ArrowClass, SpawnTransform);
		if (Arrow)
		{
			Arrow->SetArrowSpeed(ArrowSpeedVal);
			UGameplayStatics::FinishSpawningActor(Arrow, SpawnTransform);
			UGameplayStatics::PlaySoundAtLocation(this, ShootSound, MyOwner->GetActorLocation());
		}
	}
}

