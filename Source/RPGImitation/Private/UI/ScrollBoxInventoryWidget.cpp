// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScrollBoxInventoryWidget.h"
#include "UI/ItemWidget.h"
#include "Items/ItemData.h"
#include "Items/Item.h"
#include "Components/ScrollBox.h"


void UScrollBoxInventoryWidget::AddItemToInventory(class AItem* InItem)
{
	if (ItemWidgetClass && ItemScrollBox)
	{
		//UItemData* NewItemWidgetData = NewObject<UItemData>(InItem);
		//NewItemWidgetData->ItemName = InItem->ItemName.ToString();
		//NewItemWidgetData->Thumbnail = InItem->Thumbnail;

		//UItemWidget* NewItemWidget = CreateWidget<UItemWidget>(this, ItemWidgetClass);

		//if (NewItemWidget)
		//{
		//	// 아이템 정보를 설정
		//	NewItemWidget->SetItemInfo_SB(NewItemWidgetData);

		//	// ScrollBox에 추가
		//	ItemScrollBox->AddChild(NewItemWidget);
		//}
	}
}