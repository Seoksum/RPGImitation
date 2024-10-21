// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LoginSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API ULoginSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	ULoginSaveGame();

	UFUNCTION(BlueprintCallable)
	void ResetData();

	UPROPERTY()
	FDateTime LastRewardTime;

	UPROPERTY()
	int32 NextRewardDayButtonIndex;

};
