// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MailWidget.h"
#include "Items/MailData.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "UI/ReceivePostalWidget.h"
#include "UI/MailListWidget.h"

void UMailWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_MailMessage->OnClicked.AddDynamic(this, &UMailWidget::OnClickMailMessage);
	Btn_ReceiveItem->OnClicked.AddDynamic(this, &UMailWidget::OnClickReceiveItemButton);
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
	CP_Item->SetVisibility(ReceiveMail->IsInventoryItem ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	if (ReceiveMail->IsInventoryItem)
	{
		Img_Item->SetBrushFromTexture(ReceiveMail->ItemImage);
	}
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

void UMailWidget::OnClickReceiveItemButton()
{
	UMailListWidget* MailListWidget=  ReceiveMail->OwningMailListWidget;
	if (MailListWidget)
	{
		MailListWidget->RemoveMailToList(ReceiveMail);
	}
}