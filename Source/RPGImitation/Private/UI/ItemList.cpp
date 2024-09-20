// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemList.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/ListView.h"
#include "UI/ItemWidget.h"
#include "Items/Item.h"
#include "../RPGImitationCharacter.h"
#include "Items/ItemData.h"

void UItemList::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UItemList::RefreshListView()
{
	if (!NearbyItemList) return;

	// ListView에 추가할 데이터 배열 생성
	TArray<UObject*> ItemList;

	for (int32 i = 0; i < 50; i++)
	{
		ItemWidget = CreateWidget<UItemWidget>(GetOwningPlayer(), ItemWidgetClass);
		if (ItemWidget)
		{
			//ItemWidget->InitializeItemData(i);
			ItemList.Add(ItemWidget);
		}

		NearbyItemList->SetListItems(ItemList);
	}


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

