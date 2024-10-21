// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameData/RewardDataTable.h"
#include "GameData/ShopItemDataTable.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UMyGameInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable)
	bool CheckRewardDate();

	void GetReward();

	void LoadLastRewardTime();
	void SaveLastRewardTime();

	FRewardDataTable* GetRewardDataTable(int32 Day);
	FShopItemDataTable* GetShopItemDataTable(int32 Index);

	float GetUpdateTime();

protected:

	UPROPERTY(EditAnywhere, Category = "Time")
		float UpdateTime;

	UPROPERTY()
	UDataTable* RewardDataTable;

	UPROPERTY()
	UDataTable* ShopItemDataTable;

	FDateTime LastRewardDate;


};
