// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Stat/CharacterStatWidget.h"
#include "Components/TextBlock.h"


void UCharacterStatWidget::SetWeaponAttackStat(float WeaponAttack)
{
	const FString Weapon_Attack = FString::Printf(TEXT("%d"), (int)WeaponAttack);
	Text_WeaponAttack->SetText(FText::FromString(Weapon_Attack));
}

void UCharacterStatWidget::SetPlayerStat(const FStatDataTable& CharacterStat)
{
	const FString MaxHp = FString::Printf(TEXT("%d"), (int)CharacterStat.MaxHp);
	Text_MaxHp->SetText(FText::FromString(MaxHp));

	const FString MaxMana = FString::Printf(TEXT("%d"), (int)CharacterStat.MaxMana);
	Text_MaxMana->SetText(FText::FromString(MaxMana));

	const FString Attack = FString::Printf(TEXT("%d"), (int)CharacterStat.Attack);
	Text_BaseAttack->SetText(FText::FromString(Attack));

}

void UCharacterStatWidget::SetPlayerCurrentHp(float Hp)
{
	const FString CurrentHp = FString::Printf(TEXT("%d"), (int)Hp);
	Text_CurrentHp->SetText(FText::FromString(CurrentHp));
}

void UCharacterStatWidget::SetPlayerCurrentMana(float Mana)
{
	const FString CurrentMana = FString::Printf(TEXT("%d"), (int)Mana);
	Text_CurrentMana->SetText(FText::FromString(CurrentMana));
}

void UCharacterStatWidget::SetPlayerCurrentLevel(int32 Level)
{
	const FString CurrentLevel = FString::Printf(TEXT("%d"), Level);
	Text_CurrentLevel->SetText(FText::FromString(CurrentLevel));
}
