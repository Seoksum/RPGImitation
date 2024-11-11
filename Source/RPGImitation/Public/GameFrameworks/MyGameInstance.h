// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameData/RewardDataTable.h"
#include "GameData/ShopItemDataTable.h"
#include "GameData/WeaponDataTable.h"
#include "GameData/StatDataTable.h"
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

	void SetCharacterMeshIndex(USkeletalMesh* SelectedSkeletalMesh);

	UFUNCTION(BlueprintCallable)
	bool CheckRewardDate();

	void GetReward();

	void LoadLastRewardTime();
	void SaveLastRewardTime();

	FRewardDataTable* GetRewardDataTable(int32 Day);
	FShopItemDataTable* GetShopItemDataTable(int32 Index);
	FStatDataTable GetCharacterStat(int32 Level);

	float GetUpdateTime();

	USkeletalMesh* GetSelectedSkeletalMesh();


protected:

	UPROPERTY(EditAnywhere, Category = "Time")
		float UpdateTime;

	FDateTime LastRewardDate;

	UPROPERTY()
	UDataTable* RewardDataTable;

	UPROPERTY()
	UDataTable* ShopItemDataTable;

	TArray<FStatDataTable> CharacterStatTables;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	int32 MaxLevel;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	int32 CharacterMeshIdx;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	USkeletalMesh* CharacterSkeletalMesh;

};
