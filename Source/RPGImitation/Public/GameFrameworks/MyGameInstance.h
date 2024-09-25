// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameData/RewardDataTable.h"
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
	bool CheckLoginDate();

	void GetReward();

	void LoadLastLoginTime();
	void SaveLastLoginTime();

	FRewardDataTable* GetRewardDataTable(int32 Day);

protected:

	UPROPERTY(EditAnywhere, Category = "Time")
		float UpdateTime;

	UPROPERTY()
	UDataTable* RewardDataTable;

	FDateTime LastLoginDate;


};
