// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MailWidget.h"
#include "Items/MailData.h"
#include "Components/TextBlock.h"


void UMailWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UE_LOG(LogTemp, Log, TEXT("NativeOnListItemObjectSet"));

	UMailData* Mail = Cast<UMailData>(ListItemObject);
	if (Mail == nullptr)	return;

	SetMailInfo(Mail);

}

void UMailWidget::SetMailInfo(UMailData* InMail)
{
	if (nullptr == InMail) return;

	UE_LOG(LogTemp, Log, TEXT("SetMailInfo Success"));

	TextFrom->SetText(FText::FromString(InMail->Sender));
	TextContents->SetText(FText::FromString(InMail->Message));
}
