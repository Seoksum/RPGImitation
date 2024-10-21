// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScrollBoxInventoryWidget.h"
#include "UI/ItemWidget.h"
#include "UI/Mail/MailWidget.h"
#include "Items/MailData.h"
#include "Items/Item.h"
#include "Components/ScrollBox.h"


void UScrollBoxInventoryWidget::AddItemToInventory(class UMailData* InMailData)
{
	if (MailWidgetClass && MailScrollBox)
	{
		UMailData* MailData = NewObject<UMailData>();
		MailData->Sender = "Sumin";
		MailData->Title = "ScrollBox Mail";
		MailData->Thumbnail = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Contents/Images/Mails/Mail.Mail'"));


		UMailWidget* NewMailWidget = CreateWidget<UMailWidget>(this, MailWidgetClass);
		if (NewMailWidget)
		{
			// 아이템 정보를 설정
			NewMailWidget->SetMailInfo(InMailData);
			// ScrollBox에 추가
			MailScrollBox->AddChild(NewMailWidget);
		}
	}
}