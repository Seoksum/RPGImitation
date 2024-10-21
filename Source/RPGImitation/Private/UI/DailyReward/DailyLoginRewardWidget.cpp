// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DailyReward/DailyLoginRewardWidget.h"
#include "Components/GridPanel.h"
#include "GameFrameworks/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameData/RewardDataTable.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "UI/DailyReward/DailyLoginRewardButtonWidget.h"
#include "GameFrameworks/LoginSaveGame.h"

void UDailyLoginRewardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RowSize = 4;
	ColSize = 5;
	ItemCount = 20;

	GameInstance = Cast< UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	LifeSpan = GameInstance->GetUpdateTime();

	if (!IsButtonCreated)
	{
		CreateRewardInfos();
		InitGridPanel();
		IsButtonCreated = true;
	}

	if (ButtonWidget->OnRewardButtonClicked.IsBound())
	{
		ButtonWidget->OnRewardButtonClicked.RemoveAll(this);
	}
}

void UDailyLoginRewardWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UDailyLoginRewardWidget::NativeDestruct()
{
	Super::NativeDestruct();

}


void UDailyLoginRewardWidget::CreateRewardInfos()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		for (int32 i = 1; i <= ItemCount; i++)
		{
			FRewardInfo RewardInfo;
			FRewardDataTable* DT_Reward = MyGameInstance->GetRewardDataTable(i);
			if (DT_Reward)
			{
				RewardInfo.Index = i;
				RewardInfo.Day = DT_Reward->Day;
				RewardInfo.ItemName = DT_Reward->ItemName;
				const FString ImagePath = DT_Reward->ItemPath;
				RewardInfo.IsInInventory = DT_Reward->IsInventory;
				UTexture2D* ImageTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath));
				RewardInfo.ItemThumbnail = ImageTexture;
				RewardInfo.ItemType = DT_Reward->ItemType;
				RewardInfo.ConsumableType = DT_Reward->ConsumableType;
				RewardInfo.NoneConsumableType = DT_Reward->NoneConsumableType;
				RewardInfos.Add(RewardInfo);
			}
		}
	}
}

void UDailyLoginRewardWidget::InitGridPanel()
{
	int32 Row = 0;
	int32 Col = 0;
	int32 NextButtonIndex = 1;

	ULoginSaveGame* LoginSaveGame = Cast<ULoginSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("DailyRewardSaveSlot"), 0));
	if (LoginSaveGame)
	{
		NextButtonIndex = LoginSaveGame->NextRewardDayButtonIndex;
	}
	ButtonWidgetArray.Add(nullptr);
	
	for (const FRewardInfo& RewardInfo : RewardInfos)
	{
		if (ButtonWidgetClass != nullptr)
		{
			ButtonWidget = CreateWidget<UDailyLoginRewardButtonWidget>(GetWorld(), ButtonWidgetClass);
			if (ButtonWidget)
			{
				ButtonWidget->SetRewardInfo(RewardInfo);
				ButtonWidget->ButtonIndex = RewardInfo.Index;
				ButtonWidget->SetIsEnabled(RewardInfo.Index == NextButtonIndex);
				GP_Reward->AddChildToGrid(ButtonWidget, Row, Col++);
				ButtonWidget->OnRewardButtonClicked.AddUObject(this, &UDailyLoginRewardWidget::OnClickButton);
				ButtonWidgetArray.Add(ButtonWidget);
				if (Col >= ColSize)
				{
					Col = 0;
					Row++;
				}
			}
		}
	}
}

void UDailyLoginRewardWidget::OnClickButton(int32 ButtonIndex)
{
	if (ButtonWidgetArray.IsValidIndex(ButtonIndex))
	{
		ButtonWidgetArray[ButtonIndex]->SetIsEnabled(false);
	}
	int32 NextButtonIndex = (ButtonIndex + 1) % ItemCount;// 다음 버튼을 활성화
	ULoginSaveGame* SaveGameInstance = Cast<ULoginSaveGame>(UGameplayStatics::CreateSaveGameObject(ULoginSaveGame::StaticClass()));
	if (SaveGameInstance)
	{
		SaveGameInstance->NextRewardDayButtonIndex = NextButtonIndex;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("DailyRewardSaveSlot"), 0);
	}

	GameInstance = Cast< UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->SaveLastRewardTime();
		if (!GameInstance->CheckRewardDate())
		{
			GetWorld()->GetTimerManager().SetTimer(CheckLoginTimerHandle, FTimerDelegate::CreateLambda([this, NextButtonIndex] {
				SetActiveNextButton(NextButtonIndex);
				}), LifeSpan, false);
			return;
		}
		else
		{
			SetActiveNextButton(NextButtonIndex);
		}
	}
}

void UDailyLoginRewardWidget::SetActiveNextButton(int32 NextButtonIndex)
{
	if (ButtonWidgetArray.IsValidIndex(NextButtonIndex))
	{
		ButtonWidgetArray[NextButtonIndex]->SetIsEnabled(true);
	}
}
