// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/NoneConsumableItemData.h"
#include "WeaponItemData_Sword.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UWeaponItemData_Sword : public UNoneConsumableItemData
{
	GENERATED_BODY()
	

public:
	// Sets default values for this actor's properties
	UWeaponItemData_Sword();


public:

	void Attack(int32 damage, float TraceDistance, class UParticleSystem* Particle) override;

	UPROPERTY(EditDefaultsOnly)
		float Radius;


};
