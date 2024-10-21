// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Items/ItemData.h"
#include "Items/MailData.h"


void UItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


}

void UItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UMailData* MailData = Cast<UMailData>(ListItemObject);
	if (MailData == nullptr)	return;

	SetMailInfo(MailData);
}

void UItemWidget::SetMailInfo(UMailData* InMail)
{
	T_Sender->SetText(FText::FromString(InMail->Sender));
	T_Title->SetText(FText::FromString(InMail->Title));
	Img_Item->SetBrushFromTexture(InMail->Thumbnail);
}





