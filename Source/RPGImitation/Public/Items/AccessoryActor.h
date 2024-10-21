// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AccessoryActor.generated.h"

UCLASS()
class RPGIMITATION_API AAccessoryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAccessoryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void AttachAccessoryToSocket(class ARPGImitationCharacter* Character, FName SocketName, UStaticMesh* InAccessoryMesh);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		UStaticMeshComponent* AccessoryStaticMeshComponent;


};
