// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:

	AMyGameModeBase();

	virtual void BeginPlay() override;

	void IncreaseExp(AController* KillerController, float Exp);

	void PawnKilled(class APawn* PawnKilled);

	void EndGame(bool bIsPlayerWinner);

};
