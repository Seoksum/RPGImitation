// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Shop/ShopItemWidget.h"
#include "Items/ShopItemData.h"
#include "Items/ItemData.h"
#include "Items/PotionItemData.h"
#include "Items/WeaponItemData.h"
#include "Items/NoneConsumableItemData.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../RPGImitationCharacter.h"
#include "Components/InventoryComponent.h"

void UShopItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Purchase->OnClicked.AddDynamic(this, &UShopItemWidget::OnClickPurchaseButton);
}

void UShopItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	ShopItemData = Cast<UShopItemData>(ListItemObject);
	if (nullptr == ShopItemData) return;

	Img_ItemThumbnail->SetBrushFromTexture(ShopItemData->ItemData->Thumbnail);
	T_ItemName->SetText(FText::FromString(ShopItemData->ItemData->ItemName));
	T_ItemDescription->SetText(FText::FromString(ShopItemData->ItemDescription));
	FString PriceString = FString::FromInt(ShopItemData->Price);
	T_Price->SetText(FText::FromString(PriceString));
	SetItemType();
}

void UShopItemWidget::SetItemType()
{
	if (ShopItemData->ItemData->ItemType == EItemType::ITEM_Consumable)
	{
		ItemData = NewObject<UPotionItemData>();
	}
	else if (ShopItemData->ItemData->ItemType == EItemType::ITEM_NoneConsumable)
	{
		ItemData = NewObject<UNoneConsumableItemData>();
	}
	else
	{
		ItemData = NewObject<UItemData>();
	}
	ItemData->ItemName = ShopItemData->ItemData->ItemName;
	ItemData->Thumbnail = ShopItemData->ItemData->Thumbnail;
	ItemData->ItemType = ShopItemData->ItemData->ItemType;
	ItemData->ConsumableType = ShopItemData->ItemData->ConsumableType;
	ItemData->NoneConsumableType = ShopItemData->ItemData->NoneConsumableType;
}

void UShopItemWidget::OnClickPurchaseButton()
{
	ARPGImitationCharacter* PlayerCharacter = Cast<ARPGImitationCharacter>(GetOwningPlayerPawn());
	if (PlayerCharacter)
	{
		// 골드 차감
		if (!PlayerCharacter->RemoveGold(ShopItemData->Price))
			return;

		// 인벤토리에 아이템 추가
		Inventory = PlayerCharacter->GetInventoryComponent();
		if (Inventory)
		{
			Inventory->AddItem(ItemData);
		}
	}
}