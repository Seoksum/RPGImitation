// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UStatBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void BindHp(class UStatComponent* StatComp);
	void UpdateHp(float Hp);

	void BindMana(class UStatComponent* StatComp);
	void UpdateMana(float Mana, float MaxMana);


public:

	TWeakObjectPtr<class UStatComponent> PlayerStatComponent;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_ManaBar;
};
