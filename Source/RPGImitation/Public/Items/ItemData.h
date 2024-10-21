// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameData/GameEnums.h"
#include "ItemData.generated.h"

/**
 * 
 */



UCLASS()
class RPGIMITATION_API UItemData : public UObject
{
	GENERATED_BODY()

public:

    UItemData();

    virtual void UseItem(class ARPGImitationCharacter* Character);
	
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
    FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
    UTexture2D* Thumbnail;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
    EItemType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
    EConsumableType ConsumableType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
    ENoneConsumableType NoneConsumableType;
    

};

