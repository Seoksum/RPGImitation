// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Stat/StatBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/StatComponent.h"

void UStatBarWidget::BindHp(class UStatComponent* StatComp)
{
	PlayerStatComponent = StatComp;
	PlayerStatComponent->OnHpChanged.AddUObject(this, &UStatBarWidget::UpdateHp);
}

void UStatBarWidget::UpdateHp(float Hp)
{
	if (PlayerStatComponent.IsValid())
	{
		PB_HpBar->SetPercent(Hp / PlayerStatComponent->GetMaxHp());
	}

}

void UStatBarWidget::BindMana(class UStatComponent* StatComp)
{
	PlayerStatComponent = StatComp;
	PlayerStatComponent->OnManaChanged.AddUObject(this, &UStatBarWidget::UpdateMana);
}

void UStatBarWidget::UpdateMana(float Mana)
{
	if (PlayerStatComponent.IsValid())
		PB_ManaBar->SetPercent(Mana / PlayerStatComponent->GetMaxMana());
}
