// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryWidget.h"
#include "UI/Inventory/InventoryItemWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Items/ItemData.h"
#include "Kismet/GameplayStatics.h"
#include "../RPGImitationCharacter.h"
#include "Components/InventoryComponent.h"


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RowSize = 5;
	ColSize = 5;

	ARPGImitationCharacter* Player = Cast<ARPGImitationCharacter>(GetOwningPlayerPawn());
	if (Player)
	{
		Inventory = Player->GetInventoryComponent();
		if (Inventory)
		{
			Inventory->OnInventoryUpdated.RemoveAll(this);
			Inventory->OnInventoryUpdated.AddUObject(this, &UInventoryWidget::InitGrid);
		}
		InitGrid();
	}
	//if (!IsPanelCreated)
	//{
	//	InitGrid();
	//	IsPanelCreated = true;
	//}

}

void UInventoryWidget::InitGrid()
{
	UGP_ItemInventory->ClearChildren();

	if (nullptr != UGP_ItemInventory && nullptr != InventoryItemWidgetClass)
	{
		int32 Row = 0;
		int32 Col = 0;
		int32 Index = 0;
		SetCurrentItemArray(Index); // 아이템 세팅

		while (Index < RowSize * ColSize)
		{
			UInventoryItemWidget* InventoryItemWidget = CreateWidget<UInventoryItemWidget>(this, InventoryItemWidgetClass);
			if (InventoryItemWidget)
			{
				Row = Index / RowSize;
				Col = Index % ColSize;

				UItemData* NewItemData = InitItemData();
				InventoryItemWidget->SetItemInfo(NewItemData);
				UGP_ItemInventory->AddChildToUniformGrid(InventoryItemWidget, Row, Col);
				Index++;
			}
		}
	}
}

UItemData* UInventoryWidget::InitItemData()
{
	UItemData* NewItemData = NewObject<UItemData>();
	const FString NoneImage = "Texture2D'/Game/Contents/Images/Items/Inventory_none.Inventory_none'";
	UTexture2D* NoneTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *NoneImage));
	NewItemData->Thumbnail = NoneTexture;
	FString NoneName = "None";
	NewItemData->ItemName = NoneName;

	return NewItemData;
}

void UInventoryWidget::SetCurrentItemArray(int32& Index)
{
	int32 Row = 0;
	int32 Col = 0;

	TArray<class UItemData*> CurrentItems = Inventory->GetItemDataArray();
	for (auto& Item : CurrentItems)
	{
		UInventoryItemWidget* InventoryItemWidget = CreateWidget<UInventoryItemWidget>(this, InventoryItemWidgetClass);
		if (InventoryItemWidget)
		{
			Row = Index / RowSize;
			Col = Index % ColSize;
			InventoryItemWidget->SetItemInfo(Item);
			UGP_ItemInventory->AddChildToUniformGrid(InventoryItemWidget, Row, Col);
			Index++;
		}
	}
}
