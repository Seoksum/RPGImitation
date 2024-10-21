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


public:
	TWeakObjectPtr<class UStatComponent> EnemyStatComponent;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;



};
