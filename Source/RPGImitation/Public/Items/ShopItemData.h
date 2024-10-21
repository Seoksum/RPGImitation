// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ShopItemData.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UShopItemData : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	class UItemData* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	int32 Price;
};
