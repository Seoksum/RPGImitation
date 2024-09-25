// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/UIManager.h"
#include "Blueprint/UserWidget.h"
#include "UI/ItemList.h"
#include "UI/ScrollBoxInventoryWidget.h"
#include "UI/MailListWidget.h"
#include "UI/FullMailWidget.h"
#include "UI/DailyLoginRewardWidget.h"


UUIManager::UUIManager()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemListWidgetClass(TEXT("WidgetBlueprint'/Game/Contents/UI/WBP_ItemListWidget.WBP_ItemListWidget_C'"));
	if (ItemListWidgetClass.Succeeded())
	{
		InventoryWidgetClass = ItemListWidgetClass.Class;
		InventoryWidget = CreateWidget<UItemList>(GetWorld(), InventoryWidgetClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> SBItemListWidgetClass(TEXT("WidgetBlueprint'/Game/Contents/UI/WBP_ScrollBoxItemWidget.WBP_ScrollBoxItemWidget_C'"));
	if (SBItemListWidgetClass.Succeeded())
	{
		SB_InventoryWidgetClass = SBItemListWidgetClass.Class;
		SB_InventoryWidget = CreateWidget<UScrollBoxInventoryWidget>(GetWorld(), SB_InventoryWidgetClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> MailListWidgetClassRef(TEXT("WidgetBlueprint'/Game/Contents/UI/Mail/WBP_MailListWidget.WBP_MailListWidget_C'"));
	if (MailListWidgetClassRef.Succeeded())
	{
		MailListWidgetClass = MailListWidgetClassRef.Class;
		//MailListWidget = CreateWidget<UMailListWidget>(GetWorld(), MailListWidgetClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> FullMailWidgetClassRef(TEXT("WidgetBlueprint'/Game/Contents/UI/Mail/WBP_FullMailWidget.WBP_FullMailWidget_C'"));
	if (FullMailWidgetClassRef.Succeeded())
	{
		FullMailWidgetClass = FullMailWidgetClassRef.Class;
		FullMailWidget = CreateWidget<UFullMailWidget>(GetWorld(), FullMailWidgetClass);

		if (FullMailWidget && FullMailWidget->WBP_MailListWidget)
		{
			MailListWidget = FullMailWidget->WBP_MailListWidget;
		}
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> DailyRewardWidgetClassRef(TEXT("WidgetBlueprint'/Game/Contents/UI/Rewards/WBP_DailyLoginReward.WBP_DailyLoginReward_C'"));
	if (DailyRewardWidgetClassRef.Succeeded())
	{
		DailyRewardWidgetClass = DailyRewardWidgetClassRef.Class;
		DailyRewardWidget = CreateWidget<UDailyLoginRewardWidget>(GetWorld(), DailyRewardWidgetClass);
		//if (DailyRewardWidget)
		//{
		//	DailyRewardWidget->CreateRewardInfos();
		//	DailyRewardWidget->InitGridPanel();
		//	UE_LOG(LogTemp, Log, TEXT("[Daily] Init Daily Widget"));
		//}

	}


}

void UUIManager::SetUIState(EUIState NewState)
{
	CurrentUIState = NewState;
	//UpdateUI();
}

void UUIManager::UpdateUI()
{
	// 기존 위젯 제거
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	switch (CurrentUIState)
	{
	case EUIState::UI_Inventory:
		if (InventoryWidgetClass)
		{
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), InventoryWidgetClass);
		}
		break;

	case EUIState::UI_Mail:
		if (MailListWidgetClass)
		{
			CurrentWidget = CreateWidget(GetWorld(), MailListWidgetClass);
		}
		break;

	case EUIState::UI_None:
		break;
	}

	if (CurrentWidget)
	{
		CurrentWidget->AddToViewport();
		
	}
}

void UUIManager::UpdateUIState(EUIState NewState, bool IsActive)
{
	if (NewState == EUIState::UI_Inventory)
	{
		if (IsActive) { InventoryWidget->AddToViewport(); }
		else { InventoryWidget->RemoveFromViewport(); }
	}

	else if (NewState == EUIState::UI_SBInventory)
	{
		if (IsActive) { SB_InventoryWidget->AddToViewport(); }
		else { SB_InventoryWidget->RemoveFromViewport(); }
	}

	else if (NewState == EUIState::UI_Mail)
	{
		if (IsActive) { FullMailWidget->AddToViewport(); }
		else { FullMailWidget->RemoveFromViewport(); }
	}

	else if (NewState == EUIState::UI_DailyReward)
	{
		if (IsActive) { DailyRewardWidget->AddToViewport(); }
		else { DailyRewardWidget->RemoveFromViewport(); }
	}

}

EUIState UUIManager::GetCurrentUIState()
{
	return CurrentUIState;
}

void UUIManager::AddItemToInventory(class AItem* InItem)
{
	if (InventoryWidget)
	{
		InventoryWidget->AddItemToList(InItem);
	}
}

void UUIManager::SB_AddItemToInventory(class AItem* InItem)
{
	if (SB_InventoryWidget)
	{
		SB_InventoryWidget->AddItemToInventory(InItem);
	}
}

void UUIManager::AddMailToMailBox(class UMailData* InMailData)
{
	if (MailListWidget)
	{
		MailListWidget->AddMailToList(InMailData);
	}
}

