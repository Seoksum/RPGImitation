// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mail/SentPostalWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Items/MailData.h"

void USentPostalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Close->OnClicked.AddDynamic(this, &USentPostalWidget::OnClickCloseButton);
}

void USentPostalWidget::OnClickCloseButton()
{
	RemoveFromParent();
}

void USentPostalWidget::SetMailInfo(UMailData* InMailData)
{
	T_ReceiverName->SetText(FText::FromString(InMailData->Receiver));
	T_Title->SetText(FText::FromString(InMailData->Title));
	T_Contents->SetText(FText::FromString(InMailData->Message));

}

