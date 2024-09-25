// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MailWidget.h"
#include "Items/MailData.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "UI/ReceivePostalWidget.h"

void UMailWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_MailMessage->OnClicked.AddDynamic(this, &UMailWidget::OnClickMailMessage);
	IsInViewportNow = false;
}

void UMailWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UMailData* Mail = Cast<UMailData>(ListItemObject);
	if (Mail == nullptr)	return;

	CB_MailSelected->SetIsChecked(false);
	SetMailInfo(Mail);

}

void UMailWidget::SetMailInfo(UMailData* InMail)
{
	ReceiveMail = InMail;
	T_Sender->SetText(FText::FromString(ReceiveMail->Sender));
	T_Title->SetText(FText::FromString(ReceiveMail->Title));
}

void UMailWidget::OnClickMailMessage()
{
	UReceivePostalWidget* ReceivePostalWidget = CreateWidget< UReceivePostalWidget>(GetWorld(), ReceivePostalWidgetClass);
	if (ReceivePostalWidget && !IsInViewportNow)
	{
		ReceivePostalWidget->AddToViewport();
		ReceivePostalWidget->SetMail(ReceiveMail);
		ReceivePostalWidget->ParentWidget = this;
		IsInViewportNow = true;
	}
}
