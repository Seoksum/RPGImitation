// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DailyLoginRewardButtonWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "GameFrameworks/LoginSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "UI/DailyLoginRewardWidget.h"

void UDailyLoginRewardButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_AcceptItem->OnClicked.AddDynamic(this, &UDailyLoginRewardButtonWidget::OnClickAcceptButton);
}

void UDailyLoginRewardButtonWidget::SetRewardInfo(int32 Day, FText ItemName, UTexture2D* ItemThumbnail)
{
	FString DayString = FString::FromInt(Day);
	FText DayText = FText::FromString(DayString);
	T_Day->SetText(DayText);
	T_ItemName->SetText(ItemName);
	Img_ItemThumbnail->SetBrushFromTexture(ItemThumbnail);
}

void UDailyLoginRewardButtonWidget::OnClickAcceptButton()
{
	OnRewardButtonClicked.Broadcast(ButtonIndex);
	UE_LOG(LogTemp, Log, TEXT("Button Index: %d"), ButtonIndex);
	//ULoginSaveGame* LoadLoginSaveGame = Cast<ULoginSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MySaveSlot"), 0));
	//if (LoadLoginSaveGame)
	//{
	//	int32 RewardDay = LoadLoginSaveGame->LastSelectedButtonIndex;
	//	OnRewardButtonClicked.Broadcast(ButtonIndex);
	//	UE_LOG(LogTemp, Log, TEXT("Button Index: %d"), ButtonIndex);
	//	//UGameplayStatics::SaveGameToSlot(LoadLoginSaveGame, TEXT("MySaveSlot"), 0);		
	//}
}
