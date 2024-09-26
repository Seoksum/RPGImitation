// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SendMailWidget.h"
#include "Items/MailData.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "UI/SentPostalWidget.h"

void USendMailWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_MailMessage->OnClicked.AddDynamic(this, &USendMailWidget::OnClickMailMessage);
	IsInViewportNow = false;
}

void USendMailWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UMailData* Mail = Cast<UMailData>(ListItemObject);
	if (Mail == nullptr)	return;

	CB_MailSelected->SetIsChecked(false);
	SetMailInfo(Mail);

}

void USendMailWidget::SetMailInfo(UMailData* InMail)
{
	SendMail = InMail;
	T_Sender->SetText(FText::FromString(SendMail->Sender));
	T_Title->SetText(FText::FromString(SendMail->Title));
}

void USendMailWidget::OnClickMailMessage()
{
	USentPostalWidget* SentPostalWidget = CreateWidget< USentPostalWidget>(GetWorld(), SentPostalWidgetClass);
	if (SentPostalWidget && !IsInViewportNow)
	{
		SentPostalWidget->SetMailInfo(SendMail);
		SentPostalWidget->AddToViewport();
		IsInViewportNow = true;
	}
}

