// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DeathInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDeathInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPGIMITATION_API IDeathInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category = Health)
		void OnDeath();
	virtual void OnDeath_Implementation() = 0;
};
