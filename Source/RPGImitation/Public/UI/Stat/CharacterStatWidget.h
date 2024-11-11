 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/StatDataTable.h"
#include "CharacterStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UCharacterStatWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetWeaponAttackStat(float WeaponAttack);
	void SetPlayerStat(const FStatDataTable& CharacterStat);

	void SetPlayerCurrentHp(float Hp);
	void SetPlayerCurrentMana(float Mana);

	void SetPlayerCurrentLevel(int32 Level);
	
	
protected:

	//TWeakObjectPtr<class UMyStatComponent> CurrentStatComp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_CurrentLevel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_CurrentHp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_MaxHp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_CurrentMana;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_MaxMana;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_BaseAttack;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_WeaponAttack;

};
