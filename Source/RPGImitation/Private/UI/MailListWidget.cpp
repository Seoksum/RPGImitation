// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MailListWidget.h"
#include "Components/ListView.h"
#include "UI/MailWidget.h"

void UMailListWidget::AddMailToList(const FString& InMessage)
{
	if (!MailListView) return;

	

	//UItemData* NewItemWidgetData = NewObject<UItemData>(InItem);
	//if (NewItemWidgetData)
	//{
	//	NewItemWidgetData->ItemName = InItem->ItemName.ToString();
	//	NewItemWidgetData->Thumbnail = InItem->Thumbnail;
	//	MailListView->AddItem(NewItemWidgetData);
	//	MailListView->RequestRefresh();
	//}
}