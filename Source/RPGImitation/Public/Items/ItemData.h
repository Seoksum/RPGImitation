// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UItemData : public UObject
{
	GENERATED_BODY()
	
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
    FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
    UTexture2D* Thumbnail;

};

