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

	// ListView�� �߰��� ������ �迭 ����
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
		// ������ �����͸� �����ϴ� �Լ� ȣ��
		NewItemWidget->SetItemInfo(NewItemData);
		NearbyItemList->AddItem(NewItemWidget);
		NearbyItemList->RequestRefresh();
	}
}

TArray<UObject*> UItemList::GetCurrentListItems()
{
	if (NearbyItemList)
	{
		// ListView�� �ִ� ���� ������ ����� ��ȯ
		return NearbyItemList->GetListItems();
	}

	// ���� ListView�� ��ȿ���� �ʴٸ� �� �迭�� ��ȯ
	return TArray<UObject*>();
}
