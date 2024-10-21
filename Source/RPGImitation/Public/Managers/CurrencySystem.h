// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CurrencySystem.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGoldChanged, int32);

UCLASS()
class RPGIMITATION_API UCurrencySystem : public UObject
{
	GENERATED_BODY()
	
public:

	UCurrencySystem();

	void AddGold(int32 Amount);
	bool RemoveGold(int32 Amount);

	FOnGoldChanged OnGoldChanged;


protected:

	UPROPERTY(BlueprintReadWrite, Category = "Currency")
	int32 Gold;


};
