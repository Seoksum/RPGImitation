// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSkillWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UCharacterSkillWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:

	virtual void NativeConstruct() override;

public:

	void StartAttackQ();
	void StartAttackE();
	void StartAttackR();

	void EndAttackQ();
	void EndAttackE();
	void EndAttackR();


protected:

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	int32 Remaining_SkillQ;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	int32 Remaining_SkillE;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	int32 Remaining_SkillR;

	FTimerHandle QSkillHandle;
	FTimerHandle ESkillHandle;
	FTimerHandle RSkillHandle;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	class ARPGImitationCharacter* PlayerCharacter;

protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_SkillQ;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_SkillE;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_SkillR;

};
