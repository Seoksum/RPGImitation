// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Stat/CharacterSkillWidget.h"
#include "Components/TextBlock.h"
#include "../RPGImitationCharacter.h"

void UCharacterSkillWidget::NativeConstruct()
{
	PlayerCharacter = Cast<ARPGImitationCharacter>(GetOwningPlayerPawn());
}

void UCharacterSkillWidget::StartAttackQ()
{
	Remaining_SkillQ = 3;
	GetWorld()->GetTimerManager().SetTimer(QSkillHandle, this, &UCharacterSkillWidget::EndAttackQ, 1.f, true);
}

void UCharacterSkillWidget::StartAttackE()
{
	Remaining_SkillE = 4;
	GetWorld()->GetTimerManager().SetTimer(ESkillHandle, this, &UCharacterSkillWidget::EndAttackE, 1.f, true);
}

void UCharacterSkillWidget::StartAttackR()
{
	Remaining_SkillR = 5;
	GetWorld()->GetTimerManager().SetTimer(RSkillHandle, this, &UCharacterSkillWidget::EndAttackR, 1.f, true);
}

void UCharacterSkillWidget::EndAttackQ()
{
	FString Q_Str;
	if (Remaining_SkillQ < 1)
	{
		Q_Str = FString::Printf(TEXT("Q"));
		PlayerCharacter->EndAttackQ();
		GetWorld()->GetTimerManager().ClearTimer(QSkillHandle);
	}
	else
	{
		Q_Str = FString::Printf(TEXT("%01d "), Remaining_SkillQ);
	}

	T_SkillQ->SetText(FText::FromString(Q_Str));
	--Remaining_SkillQ;
}

void UCharacterSkillWidget::EndAttackE()
{
	FString E_Str;
	if (Remaining_SkillE < 1)
	{
		E_Str = FString::Printf(TEXT("E"));
		PlayerCharacter->EndAttackE();
		GetWorld()->GetTimerManager().ClearTimer(ESkillHandle);
	}
	else
	{
		E_Str = FString::Printf(TEXT("%01d "), Remaining_SkillE);
	}

	T_SkillE->SetText(FText::FromString(E_Str));
	--Remaining_SkillE;
}

void UCharacterSkillWidget::EndAttackR()
{
	FString R_Str;

	if (Remaining_SkillR < 1)
	{
		R_Str = FString::Printf(TEXT("R"));
		PlayerCharacter->EndAttackR();
		GetWorld()->GetTimerManager().ClearTimer(RSkillHandle);
	}

	else
	{
		R_Str = FString::Printf(TEXT("%01d "), Remaining_SkillR);
	}
	T_SkillR->SetText(FText::FromString(R_Str));
	--Remaining_SkillR;
}