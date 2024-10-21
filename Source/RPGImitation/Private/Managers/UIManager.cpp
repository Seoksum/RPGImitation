// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/UIManager.h"
#include "Blueprint/UserWidget.h"
#include "UI/ItemList.h"
#include "UI/ScrollBoxInventoryWidget.h"
#include "UI/Mail/MailListWidget.h"
#include "UI/Mail/SendMailListWidget.h"
#include "UI/Mail/FullMailWidget.h"
#include "UI/DailyReward/DailyLoginRewardWidget.h"
#include "UI/Chat/ChatWidget.h"
#include "UI/Inventory/InventoryWidget.h"
#include "UI/Shop/ShopItemListWidget.h"
#include "UI/Stat/CharacterSkillWidget.h"


UUIManager::UUIManager()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> LVItemListWidgetClass(TEXT("WidgetBlueprint'/Game/Contents/UI/WBP_ItemListWidget.WBP_ItemListWidget_C'"));
	if (LVItemListWidgetClass.Succeeded())
	{
		LV_InventoryWidgetClass = LVItemListWidgetClass.Class;
		LV_InventoryWidget = CreateWidget<UItemList>(GetWorld(), LV_InventoryWidgetClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> SBItemListWidgetClass(TEXT("WidgetBlueprint'/Game/Contents/UI/WBP_ScrollBoxItemWidget.WBP_ScrollBoxItemWidget_C'"));
	if (SBItemListWidgetClass.Succeeded())
	{
		SB_InventoryWidgetClass = SBItemListWidgetClass.Class;
		SB_InventoryWidget = CreateWidget<UScrollBoxInventoryWidget>(GetWorld(), SB_InventoryWidgetClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> MailListWidgetClassRef(TEXT("WidgetBlueprint'/Game/Contents/UI/Mail/WBP_MailListWidget.WBP_MailListWidget_C'"));
	if (MailListWidgetClassRef.Succeeded())
	{
		MailListWidgetClass = MailListWidgetClassRef.Class;
		//MailListWidget = CreateWidget<UMailListWidget>(GetWorld(), MailListWidgetClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> FullMailWidgetClassRef(TEXT("WidgetBlueprint'/Game/Contents/UI/Mail/WBP_FullMailWidget.WBP_FullMailWidget_C'"));
	if (FullMailWidgetClassRef.Succeeded())
	{
		FullMailWidgetClass = FullMailWidgetClassRef.Class;
		FullMailWidget = CreateWidget<UFullMailWidget>(GetWorld(), FullMailWidgetClass);

		if (FullMailWidget && FullMailWidget->WBP_MailListWidget)
		{
			MailListWidget = FullMailWidget->WBP_MailListWidget;
			SendMailListWidget = FullMailWidget->WBP_SendMailListWidget;
		}
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> DailyRewardWidgetClassRef(TEXT("WidgetBlueprint'/Game/Contents/UI/Rewards/WBP_DailyLoginReward.WBP_DailyLoginReward_C'"));
	if (DailyRewardWidgetClassRef.Succeeded())
	{
		DailyRewardWidgetClass = DailyRewardWidgetClassRef.Class;
		DailyRewardWidget = CreateWidget<UDailyLoginRewardWidget>(GetWorld(), DailyRewardWidgetClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryWidgetClassRef(TEXT("WidgetBlueprint'/Game/Contents/UI/Inventory/WBP_InventoryWidget.WBP_InventoryWidget_C'"));
	if (InventoryWidgetClassRef.Succeeded())
	{
		InventoryWidgetClass = InventoryWidgetClassRef.Class;
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> ShopWidgetClassRef(TEXT("WidgetBlueprint'/Game/Contents/UI/Shop/WBP_ShopItemListWidget.WBP_ShopItemListWidget_C'"));
	if (ShopWidgetClassRef.Succeeded())
	{
		ShopWidgetClass = ShopWidgetClassRef.Class;
		ShopWidget = CreateWidget<UShopItemListWidget>(GetWorld(), ShopWidgetClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> WinScreenWidgetClassRef(TEXT("WidgetBlueprint'/Game/Contents/UI/WBP_WinScreenWidget.WBP_WinScreenWidget_C'"));
	if (WinScreenWidgetClassRef.Succeeded())
	{
		WinScreenWidgetClass = WinScreenWidgetClassRef.Class;
		WinScreenWidget = CreateWidget(GetWorld(), WinScreenWidgetClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> LoseScreenWidgetClassRef(TEXT("WidgetBlueprint'/Game/Contents/UI/WBP_LoseScreenWidget.WBP_LoseScreenWidget_C'"));
	if (LoseScreenWidgetClassRef.Succeeded())
	{
		LoseScreenWidgetClass = LoseScreenWidgetClassRef.Class;
		LoseScreenWidget = CreateWidget(GetWorld(), LoseScreenWidgetClass);
	}

}

void UUIManager::UpdateUIState(EUIState NewState, bool IsActive)
{
	if (NewState == EUIState::UI_Inventory)
	{
		if (IsActive) { InventoryWidget->AddToViewport(); }
		else { InventoryWidget->RemoveFromViewport(); }
	}

	else if (NewState == EUIState::UI_LVInventory)
	{
		if (IsActive) { LV_InventoryWidget->AddToViewport(); }
		else { LV_InventoryWidget->RemoveFromViewport(); }
	}

	else if (NewState == EUIState::UI_SBInventory)
	{
		if (IsActive) { SB_InventoryWidget->AddToViewport(); }
		else { SB_InventoryWidget->RemoveFromViewport(); }
	}

	else if (NewState == EUIState::UI_Mail)
	{
		if (IsActive) { FullMailWidget->AddToViewport(); }
		else { FullMailWidget->RemoveFromViewport(); }
	}

	else if (NewState == EUIState::UI_DailyReward)
	{
		if (IsActive) { DailyRewardWidget->AddToViewport(); }
		else { DailyRewardWidget->RemoveFromViewport(); }
	}

	else if (NewState == EUIState::UI_Shop)
	{
		if (IsActive)
		{ 
			if(ShopWidget && !ShopWidget->IsInViewport())
				ShopWidget->AddToViewport(); 
		}
		else
		{ 
			if (ShopWidget->IsInViewport())
			{
				ShopWidget->RemoveFromViewport();
			}
		}
	}

	else if (NewState == EUIState::UI_WinScreen)
	{
		if (IsActive) { WinScreenWidget->AddToViewport(); }
		else { WinScreenWidget->RemoveFromViewport(); }
	}

	else if (NewState == EUIState::UI_LoseScreen)
	{
		if (IsActive) { LoseScreenWidget->AddToViewport(); }
		else { LoseScreenWidget->RemoveFromViewport(); }
	}
}

void UUIManager::AddMailToLV(class UMailData* InMailData)
{
	if (LV_InventoryWidget)
	{
		LV_InventoryWidget->AddMailToList(InMailData);
	}
}

void UUIManager::AddMailToSB(class UMailData* InMailData)
{
	if (SB_InventoryWidget)
	{
		SB_InventoryWidget->AddItemToInventory(InMailData);
	}
}

void UUIManager::AddReceivedMailToMailBox(class UMailData* InMailData)
{
	if (MailListWidget)
	{
		MailListWidget->AddMailToList(InMailData);
	}
}

void UUIManager::AddMailToSendMailBox(class UMailData* InMailData)
{
	if (SendMailListWidget)
	{
		SendMailListWidget->AddMailToList(InMailData);
	}
}

UChatWidget* UUIManager::GetChatWidget()
{
	if (!ChatWidget)
	{
		ChatWidget = CreateWidget<UChatWidget>(GetWorld(), ChatWidgetClass);
	}

	return ChatWidget;
}

void UUIManager::SetInGameWidget(UUserWidget* InWidget)
{
	if (InWidget)
	{
		InGameWidget = InWidget;
		CharacterSkillWidget = Cast<UCharacterSkillWidget>(InGameWidget->GetWidgetFromName(TEXT("WBP_CharacterSkillWidget")));
	}
}

void UUIManager::StartSkillAttackQ()
{
	if (CharacterSkillWidget) { CharacterSkillWidget->StartAttackQ(); }
}

void UUIManager::StartSkillAttackE()
{
	if (CharacterSkillWidget) { CharacterSkillWidget->StartAttackE(); }
}

void UUIManager::StartSkillAttackR()
{
	if (CharacterSkillWidget) { CharacterSkillWidget->StartAttackR(); }
}

