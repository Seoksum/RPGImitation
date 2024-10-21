// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GoldWidget.h"
#include "Components/TextBlock.h"
#include "../RPGImitationCharacter.h"
#include "Managers/CurrencySystem.h"

void UGoldWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Log, TEXT("GoldWidget::NativeConstruct()"));

	ARPGImitationCharacter* Player = Cast<ARPGImitationCharacter>(GetOwningPlayerPawn());
	if (Player)
	{
		UCurrencySystem* CurrencySystem = Player->GetCurrencySystem();
		if (CurrencySystem)
		{
			CurrencySystem->OnGoldChanged.AddUObject(this, &UGoldWidget::GoldTextChanged);

		}
	}
}

void UGoldWidget::GoldTextChanged(int32 Gold)
{
	FText GoldText = FText::AsNumber(Gold);
	T_Gold->SetText(GoldText);
}