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
		//	// ������ ������ ����
		//	NewItemWidget->SetItemInfo_SB(NewItemWidgetData);

		//	// ScrollBox�� �߰�
		//	ItemScrollBox->AddChild(NewItemWidget);
		//}
	}
}