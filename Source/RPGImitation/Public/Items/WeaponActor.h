// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class RPGIMITATION_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AWeaponActor();

protected:

	virtual void BeginPlay() override;


public:

	void AttachWeaponToSocket(class ARPGImitationCharacter* Character, FName SocketName, USkeletalMesh* InWeaponMesh);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMeshComponent;


};
