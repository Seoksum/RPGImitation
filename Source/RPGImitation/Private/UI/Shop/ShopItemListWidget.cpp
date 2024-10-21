// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/ShopItemListWidget.h"
#include "Items/ShopItemData.h"
#include "Items/ItemData.h"
#include "Engine/DataTable.h"
#include "GameData/ShopItemDataTable.h"
#include "GameFrameworks/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ListView.h"

void UShopItemListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ItemCount = 8;

	if (!IsShopCreated)
	{
		InitShopListWidget();
		IsShopCreated = true;
	}
}

void UShopItemListWidget::InitShopListWidget()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		for (int i = 0; i < ItemCount; i++)
		{
			FShopItemDataTable* ShopItemDataTable = MyGameInstance->GetShopItemDataTable(i);
			if (ShopItemDataTable)
			{
				UItemData* ItemData = MakeItemData(ShopItemDataTable);
				ShopItem = NewObject<UShopItemData>();
				ShopItem->ItemData = ItemData;
				ShopItem->ItemDescription = ShopItemDataTable->ItemDescription;
				ShopItem->Price = ShopItemDataTable->Price;
				ShopListView->AddItem(ShopItem);
			}
		}
	}
}

UItemData* UShopItemListWidget::MakeItemData(FShopItemDataTable* ShopItemDataTable)
{
	UItemData* ItemData = NewObject<UItemData>();
	ItemData->ItemName = ShopItemDataTable->ItemName;
	UTexture2D* ImageTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *(ShopItemDataTable->ItemPath)));
	ItemData->Thumbnail = ImageTexture;
	ItemData->ItemType = ShopItemDataTable->ItemType;
	ItemData->ConsumableType = ShopItemDataTable->ConsumableType;
	ItemData->NoneConsumableType = ShopItemDataTable->NoneConsumableType;

	return ItemData;
}
