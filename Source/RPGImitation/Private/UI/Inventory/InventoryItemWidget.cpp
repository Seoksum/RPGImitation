// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryItemWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Items/ItemData.h"
#include "Items/PotionItemData.h"
#include "Items/NoneConsumableItemData.h"
#include "../RPGImitationCharacter.h"

void UInventoryItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Btn_ItemButton->OnClicked.AddDynamic(this, &UInventoryItemWidget::OnClickUseItem);

	Btn_ItemButton->OnClicked.RemoveDynamic(this, &UInventoryItemWidget::OnClickUseItem);
	Btn_ItemButton->OnClicked.AddDynamic(this, &UInventoryItemWidget::OnClickUseItem);
	//Btn_ItemButton->ToolTipTextDelegate.BindUFunction(this, FName("GetToolTipUseButton"));

	GoldAmount = 500;
}

void UInventoryItemWidget::SetItemInfo(UItemData* InItem)
{
	ItemData = InItem;
	if (ItemData)
		Img_ItemImage->SetBrushFromTexture(ItemData->Thumbnail);
}

FText UInventoryItemWidget::GetToolTipUseButton()
{
	return (("{0}"), FText::FromString(ItemData->ItemName));
}

void UInventoryItemWidget::OnClickUseItem()
{
	ARPGImitationCharacter* Player = Cast<ARPGImitationCharacter>(GetOwningPlayerPawn());
	if (Player)
	{
		if (ItemData)
		{
			if (ItemData->ItemType == EItemType::ITEM_Consumable)
			{
				Player->UseInventoryItem(ItemData);
				UPotionItemData* PotionItem = Cast<UPotionItemData>(ItemData);
				if (PotionItem)
				{
					PotionItem->UseItem(Player);
				}	
			}
			else if (ItemData->ItemType == EItemType::ITEM_NoneConsumable)
			{
				UNoneConsumableItemData* NoneConsumableItem = Cast<UNoneConsumableItemData>(ItemData);
				if (NoneConsumableItem)
				{
					NoneConsumableItem->UseItem(Player);
				}
			}
		}
		
	}
}
