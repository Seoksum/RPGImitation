// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GoldWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UGoldWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	void GoldTextChanged(int32 Gold);

protected:

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* T_Gold;

};
