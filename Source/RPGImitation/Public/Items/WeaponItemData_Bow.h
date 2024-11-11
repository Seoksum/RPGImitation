// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/NoneConsumableItemData.h"
#include "WeaponItemData_Bow.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UWeaponItemData_Bow : public UNoneConsumableItemData
{
	GENERATED_BODY()
	

public:

	UWeaponItemData_Bow();

	void Attack() override;



public:


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AArrow> ArrowClass;

	UPROPERTY(EditDefaultsOnly)
	class AArrow* Arrow;

	UPROPERTY(EditDefaultsOnly)
	float ArrowSpeedVal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* ShootSound;
};
