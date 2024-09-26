// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FullMailWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/WidgetSwitcher.h"
#include "UI/MailListWidget.h"
#include "UI/SendMailListWidget.h"

void UFullMailWidget::NativeConstruct()
{
	Super::NativeConstruct();


	Btn_ReceiveMail->OnClicked.AddDynamic(this, &UFullMailWidget::ClickReceiveMailButton);
	Btn_SendMail->OnClicked.AddDynamic(this, &UFullMailWidget::ClickSendMailButton);
	Btn_DeleteMail->OnClicked.AddDynamic(this, &UFullMailWidget::ClickDeleteMailButton);
	CB_CheckAllMail->OnCheckStateChanged.AddDynamic(this, &UFullMailWidget::ChangeAllMailCheckBox);
}


void UFullMailWidget::ClickReceiveMailButton()
{
	WBP_MailListWidget->SetVisibility(ESlateVisibility::Visible);
}

void UFullMailWidget::ClickSendMailButton()
{
	WBP_MailListWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UFullMailWidget::ClickDeleteMailButton()
{
	if (WS_Mail->GetActiveWidgetIndex() == 0)
	{
		WBP_MailListWidget->RemoveCheckedMailToList();
	}
	else if (WS_Mail->GetActiveWidgetIndex() == 1)
	{
		WBP_SendMailListWidget->RemoveCheckedMailToList();
	}
}

void UFullMailWidget::ChangeAllMailCheckBox(bool IsChecked)
{
	WBP_MailListWidget->CheckAllMail(IsChecked);
}

