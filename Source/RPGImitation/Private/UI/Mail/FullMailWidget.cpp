// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mail/FullMailWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/WidgetSwitcher.h"
#include "UI/Mail/MailListWidget.h"
#include "UI/Mail/SendMailListWidget.h"

void UFullMailWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_ReceiveMail->OnClicked.IsAlreadyBound(this, &UFullMailWidget::ClickReceiveMailButton))
	{
		Btn_ReceiveMail->OnClicked.RemoveDynamic(this, &UFullMailWidget::ClickReceiveMailButton);
		Btn_ReceiveMail->OnClicked.AddDynamic(this, &UFullMailWidget::ClickReceiveMailButton);
	}

	if (Btn_SendMail->OnClicked.IsAlreadyBound(this, &UFullMailWidget::ClickSendMailButton))
	{
		Btn_SendMail->OnClicked.RemoveDynamic(this, &UFullMailWidget::ClickSendMailButton);
		Btn_SendMail->OnClicked.AddDynamic(this, &UFullMailWidget::ClickSendMailButton);
	}

	CB_CheckAllMail->SetIsChecked(false);
	CB_CheckAllMail->OnCheckStateChanged.RemoveDynamic(this, &UFullMailWidget::ChangeAllMailCheckBox);
	CB_CheckAllMail->OnCheckStateChanged.AddDynamic(this, &UFullMailWidget::ChangeAllMailCheckBox);

	//Btn_DeleteMail->OnClicked.RemoveDynamic(this, &UFullMailWidget::ClickDeleteMailButton);
	//Btn_DeleteMail->OnClicked.AddDynamic(this, &UFullMailWidget::ClickDeleteMailButton);
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
	if (WS_Mail->GetActiveWidgetIndex() == 0)
	{
		WBP_MailListWidget->CheckAllMail(IsChecked);
	}
	else if (WS_Mail->GetActiveWidgetIndex() == 1)
	{
		WBP_SendMailListWidget->CheckAllMail(IsChecked);
	}
}

