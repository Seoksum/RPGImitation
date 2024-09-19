// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/UIManager.h"
#include "Blueprint/UserWidget.h"
#include "UI/ItemList.h"

UUIManager::UUIManager()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ItemListWidgetClass(TEXT("WidgetBlueprint'/Game/Contents/UI/WBP_ItemListWidget.WBP_ItemListWidget_C'"));
	if (ItemListWidgetClass.Succeeded())
	{
		InventoryWidgetClass = ItemListWidgetClass.Class;
		InventoryWidget = CreateWidget<UItemList>(GetWorld(), InventoryWidgetClass);
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
			ShowListWidget();
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
			//InventoryWidget = CreateWidget<UItemList>(GetWorld(), InventoryWidgetClass);
			InventoryWidget->AddToViewport();
		}
		else
		{
			InventoryWidget->RemoveFromViewport();
			//InventoryWidget = nullptr;
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

void UUIManager::ShowListWidget()
{
	UItemList* ItemListWidget = Cast<UItemList>(CurrentWidget);
	if (ItemListWidget)
	{
		TArray<UObject*> Items = ItemListWidget->GetCurrentListItems();

		// 아이템 목록을 로그로 출력
		for (UObject* Item : Items)
		{
			if (Item)
			{
				UE_LOG(LogTemp, Warning, TEXT("Item: %s"), *Item->GetName());
			}
		}
	}
}

