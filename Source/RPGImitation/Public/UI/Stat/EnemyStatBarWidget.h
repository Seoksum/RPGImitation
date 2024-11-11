// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyStatBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UEnemyStatBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void BindHp(class UStatComponent* StatComp);
	void UpdateHp(float Hp);

	void BindLevel(int32 InLevel);


public:
	TWeakObjectPtr<class UStatComponent> EnemyStatComponent;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Level;

};
