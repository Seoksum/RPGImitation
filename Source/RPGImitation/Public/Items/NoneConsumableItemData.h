// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemData.h"
#include "NoneConsumableItemData.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UNoneConsumableItemData : public UItemData
{
	GENERATED_BODY()
	
public:

	virtual void UseItem(class ARPGImitationCharacter* Character) override;

	FString GetSocketName();
};
