// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/UIManager.h"
#include "Blueprint/UserWidget.h"
#include "UI/ItemList.h"
#include "UI/ScrollBoxInventoryWidget.h"

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

	case EUIState::UI_Map:
		if (MapWidgetClass)
		{
			CurrentWidget = CreateWidget(GetWorld(), MapWidgetClass);
		}
		break;

	case EUIState::UI_MainMenu:
		if (MainMenuWidgetClass)
		{
			CurrentWidget = CreateWidget(GetWorld(), MainMenuWidgetClass);
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
		if (IsActive)
		{
			InventoryWidget->AddToViewport();
		}
		else
		{
			InventoryWidget->RemoveFromViewport();
		}
	}

	else if (NewState == EUIState::UI_SBInventory)
	{
		if (IsActive)
		{
			SB_InventoryWidget->AddToViewport();
		}
		else
		{
			SB_InventoryWidget->RemoveFromViewport();
		}
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

