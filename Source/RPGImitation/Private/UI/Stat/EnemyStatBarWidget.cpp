// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Stat/EnemyStatBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/StatComponent.h"


void UEnemyStatBarWidget::BindHp(class UStatComponent* StatComp)
{
	EnemyStatComponent = StatComp;
	EnemyStatComponent->OnHpChanged.AddUObject(this, &UEnemyStatBarWidget::UpdateHp);

}

void UEnemyStatBarWidget::UpdateHp(float Hp)
{
	if (EnemyStatComponent.IsValid())
		PB_HpBar->SetPercent(Hp / EnemyStatComponent->GetMaxHp());
}

void UEnemyStatBarWidget::BindLevel(int32 InLevel)
{
	const FString MyLevel = FString::Printf(TEXT("%d"), InLevel);
	Text_Level->SetText(FText::FromString(MyLevel));
}


