// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemList.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/ListView.h"
#include "UI/ItemWidget.h"
#include "Items/Item.h"
#include "../RPGImitationCharacter.h"


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

void UItemList::AddItemToList(class AItem* NewItemData)
{
	if (!NearbyItemList) return;

	UItemWidget* NewItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidgetClass);
	if (NewItemWidget)
	{
		// 아이템 데이터를 설정하는 함수 호출
		NewItemWidget->SetItemInfo(NewItemData);
		NearbyItemList->AddItem(NewItemWidget);
		NearbyItemList->RequestRefresh();
	}
}

TArray<UObject*> UItemList::GetCurrentListItems()
{
	if (NearbyItemList)
	{
		// ListView에 있는 현재 아이템 목록을 반환
		return NearbyItemList->GetListItems();
	}

	// 만약 ListView가 유효하지 않다면 빈 배열을 반환
	return TArray<UObject*>();
}
