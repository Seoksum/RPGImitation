// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemWidget.h"
#include "Items/Item.h"
#include "Components/TextBlock.h"
#include "Items/Item.h"
#include "Components/Image.h"


void UItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


}

void UItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	AItem* Item = Cast<AItem>(ListItemObject);
	if (Item == nullptr)	return;
	
	UE_LOG(LogTemp, Log, TEXT("NativeOnListItemObjectSet"));
	SetItemInfo(Item);
}

void UItemWidget::SetItemInfo(class AItem* InItem)
{
	if (nullptr == InItem) return;

	FText Name = InItem->ItemName;
	FText Temp = FText::FromString("Test !! ");
	ItemName->SetText(Temp);
	UE_LOG(LogTemp, Log, TEXT("[Widget]Item Name : %s"), *Name.ToString());

	UTexture2D* ThumbnailImage = InItem->Thumbnail;
	ItemImage->SetBrushFromTexture(ThumbnailImage);
}


