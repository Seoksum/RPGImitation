// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameData/GameEnums.h"
#include "RewardDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRewardDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	FRewardDataTable() : Day(0), ItemName("None"), ItemPath("None"),IsInventory(true) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString ItemPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool IsInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EConsumableType ConsumableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ENoneConsumableType NoneConsumableType;

};
