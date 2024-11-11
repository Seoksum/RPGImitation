// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemData.h"
#include "GameData/GameEnums.h"
#include "PotionItemData.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UPotionItemData : public UItemData
{
	GENERATED_BODY()
	
public:

	UPotionItemData();

	virtual void UseItem(class ARPGImitationCharacter* Character) override;

public:

	float PotionAmount;


};
