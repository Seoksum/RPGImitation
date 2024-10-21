// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemList.h"
#include "Components/ListView.h"
#include "UI/ItemWidget.h"
#include "Items/Item.h"
#include "Items/MailData.h"
#include "Items/ItemData.h"

void UItemList::NativeConstruct()
{
	Super::NativeConstruct();
	
	MailData = NewObject<UMailData>();
	MailData->Sender = "Sender";
	MailData->Title = "ListViewMailTitle";
	MailData->Thumbnail = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Contents/Images/Mails/Mail.Mail'"));
}


void UItemList::AddMailToList(class UMailData* InMailData)
{
	if (!NearbyItemList) return;

	MailData = NewObject<UMailData>();
	MailData->Sender = "Sender";
	MailData->Title = "ListViewMailTitle";

	MailData->Thumbnail = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Contents/Images/Mails/Mail.Mail'"));
	InMailData->Thumbnail = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Contents/Images/Mails/Mail.Mail'"));
	if (MailData)
	{
		NearbyItemList->AddItem(InMailData);
		//NearbyItemList->ScrollToBottom();
		//NearbyItemList->RequestRefresh();
	}

	//UItemWidget* NewItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidgetClass);
	//if (NewItemWidget)
	//{
	//	NewItemWidget->SetItemInfo(NewItemData);
	//	NearbyItemList->AddItem(NewItemWidget);
	//	NearbyItemList->RequestRefresh();
	//}
}

