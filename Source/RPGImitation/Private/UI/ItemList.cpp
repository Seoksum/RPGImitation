// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemList.h"
#include "Components/ListView.h"
#include "UI/ItemWidget.h"
#include "Items/Item.h"
#include "Items/ItemData.h"

void UItemList::NativeConstruct()
{
	Super::NativeConstruct();
	
}


void UItemList::AddItemToList(class AItem* InItem)
{
	if (!NearbyItemList) return;

	UItemData* NewItemWidgetData = NewObject<UItemData>(InItem);
	if (NewItemWidgetData)
	{
		NewItemWidgetData->ItemName = InItem->ItemName.ToString();
		NewItemWidgetData->Thumbnail = InItem->Thumbnail;

		NearbyItemList->AddItem(NewItemWidgetData);
		NearbyItemList->RequestRefresh();
	}

	//UItemWidget* NewItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidgetClass);
	//if (NewItemWidget)
	//{
	//	NewItemWidget->SetItemInfo(NewItemData);
	//	NearbyItemList->AddItem(NewItemWidget);
	//	NearbyItemList->RequestRefresh();
	//}
}

