// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RewardDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRewardDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		int32 Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		FString ItemPath;

};
