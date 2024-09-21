// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Items/ItemData.h"


void UItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


}

void UItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UE_LOG(LogTemp, Log, TEXT("NativeOnListItemObjectSet "));
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UItemData* Item = Cast<UItemData>(ListItemObject);
	if (Item == nullptr)	return;

	SetItemInfo(Item);
}

void UItemWidget::SetItemInfo(UItemData* InItem)
{
	if (nullptr == InItem) return;

	FText Name = FText::FromString(InItem->ItemName);
	ItemName->SetText(Name);

	UTexture2D* ThumbnailImage = InItem->Thumbnail;
	ItemImage->SetBrushFromTexture(ThumbnailImage);
}



