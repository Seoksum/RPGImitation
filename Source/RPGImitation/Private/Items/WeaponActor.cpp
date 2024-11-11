// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponActor.h"
#include "../RPGImitationCharacter.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponActor::AttachWeaponToSocket(class ARPGImitationCharacter* Character, FName SocketName, USkeletalMesh* InWeaponMesh)
{
	if (Character && InWeaponMesh)
	{
		USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
		WeaponMeshComponent->SetSkeletalMesh(InWeaponMesh);
		WeaponMeshComponent->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
	}
	//SnapToTargetNotIncludingScale
}


FVector AWeaponActor::GetMuzzleSocketLocation(const FName& SocketName)
{
	return WeaponMeshComponent->GetSocketLocation(SocketName);
}