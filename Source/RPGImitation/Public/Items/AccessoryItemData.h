// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemData.h"
#include "AccessoryItemData.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UAccessoryItemData : public UItemData
{
	GENERATED_BODY()
	
public:

	virtual void UseItem(class ARPGImitationCharacter* Character) override;

};
