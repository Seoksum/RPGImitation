// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/AccessoryActor.h"
#include "../RPGImitationCharacter.h"


AAccessoryActor::AAccessoryActor()
{
	AccessoryStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	AccessoryStaticMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	AccessoryStaticMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
	AccessoryStaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));

}

void AAccessoryActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAccessoryActor::AttachAccessoryToSocket(class ARPGImitationCharacter* Character, FName SocketName, UStaticMesh* InAccessoryMesh)
{
	if (Character && InAccessoryMesh)
	{
		USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
		AccessoryStaticMeshComponent->SetStaticMesh(InAccessoryMesh);
		AccessoryStaticMeshComponent->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	}
}


