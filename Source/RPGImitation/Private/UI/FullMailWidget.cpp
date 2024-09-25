// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FullMailWidget.h"
#include "Components/Button.h"
#include "UI/MailListWidget.h"

void UFullMailWidget::NativeConstruct()
{
	Super::NativeConstruct();


	Btn_ReceiveMail->OnClicked.AddDynamic(this, &UFullMailWidget::ClickReceiveMailButton);
	Btn_SendMail->OnClicked.AddDynamic(this, &UFullMailWidget::ClickSendMailButton);
	Btn_DeleteMail->OnClicked.AddDynamic(this, &UFullMailWidget::ClickDeleteMailButton);
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
	WBP_MailListWidget->RemoveCheckedMailToList();
}