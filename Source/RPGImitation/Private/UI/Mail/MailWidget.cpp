// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mail/MailWidget.h"
#include "Items/MailData.h"
#include "Items/NoneConsumableItemData.h"
#include "Items/PotionItemData.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/CanvasPanel.h"
#include "Components/InventoryComponent.h"
#include "Components/Image.h"
#include "UI/Mail/ReceivePostalWidget.h"
#include "UI/Mail/MailListWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../RPGImitationCharacter.h"

#include "Items/ItemData.h"

void UMailWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_MailMessage->OnClicked.AddDynamic(this, &UMailWidget::OnClickReceivedMailMessage);
	Btn_ReceiveItem->OnClicked.AddDynamic(this, &UMailWidget::OnClickReceiveItemButton);
	IsInViewportNow = false;
	RewardGold = 500;
	CB_MailSelected->SetIsChecked(false);
}

void UMailWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UMailData* Mail = Cast<UMailData>(ListItemObject);
	if (Mail == nullptr)	return;

	SetMailInfo(Mail);
}

void UMailWidget::SetMailInfo(UMailData* InMail)
{
	ReceiveMail = InMail;
	T_Sender->SetText(FText::FromString(ReceiveMail->Sender));
	T_Title->SetText(FText::FromString(ReceiveMail->Title));
	Img_Item->SetBrushFromTexture(ReceiveMail->Thumbnail);
}

void UMailWidget::OnClickReceivedMailMessage()
{
	UReceivePostalWidget* ReceivePostalWidget = CreateWidget< UReceivePostalWidget>(GetWorld(), ReceivePostalWidgetClass);
	if (ReceivePostalWidget && !IsInViewportNow)
	{
		ReceivePostalWidget->AddToViewport();
		ReceivePostalWidget->SetMail(ReceiveMail);
		ReceivePostalWidget->ParentWidget = this;
		IsInViewportNow = true;
	}
}

void UMailWidget::OnClickReceiveItemButton()
{
	// MailListView에서 제거하고
	UMailListWidget* MailListWidget=  ReceiveMail->OwningMailListWidget;
	if (MailListWidget)
	{
		MailListWidget->RemoveMailToList(ReceiveMail);
	}

	// 아이템을 인벤토리창에 추가
	if (nullptr != ReceiveMail->ItemData)
	{
		Character = Cast<ARPGImitationCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (Character)
		{
			Inventory = Character->GetInventoryComponent();
			if (Inventory)
			{
				if (ReceiveMail->IsInventoryItem)
				{
					if (ReceiveMail->ItemData->ItemType == EItemType::ITEM_Consumable)
					{
						UPotionItemData* PotionItem = Cast<UPotionItemData>(ReceiveMail->ItemData);
						Inventory->AddItem(PotionItem);
					}
					else if (ReceiveMail->ItemData->ItemType == EItemType::ITEM_NoneConsumable)
					{
						UNoneConsumableItemData* NoneConsumableItem = Cast<UNoneConsumableItemData>(ReceiveMail->ItemData);
						Inventory->AddItem(NoneConsumableItem);
					}
				}
				else
				{
					if (ReceiveMail->ItemData->ItemType == EItemType::ITEM_Gold)
					{
						Character->AddGold(RewardGold);
					}
				}
			}
		}
	}
}

