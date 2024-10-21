// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DailyReward/DailyLoginRewardButtonWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFrameworks/LoginSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "UI/DailyReward/DailyLoginRewardWidget.h"
#include "Items/MailData.h"
#include "Items/ItemData.h"
#include "Items/PotionItemData.h"
#include "Items/WeaponItemData.h"
#include "Items/NoneConsumableItemData.h"
#include "Managers/UIManager.h"
#include "Characters/MyPlayerController.h"

void UDailyLoginRewardButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	// 출석아이콘 3번 누르고 수령 누르면 메일도 3개가 옴 
	// => 출석체크아이콘 클릭시 계속 UDailyLoginRewardWidget이 나오는데 클릭 할 때마다 출석체크일수도 올라가는 걸 방지
	// 메일도 그만큼 옴
	if (Btn_AcceptItem->OnClicked.IsAlreadyBound(this, &UDailyLoginRewardButtonWidget::OnClickAcceptButton))
	{
		Btn_AcceptItem->OnClicked.RemoveDynamic(this, &UDailyLoginRewardButtonWidget::OnClickAcceptButton);
	}
	Btn_AcceptItem->OnClicked.AddDynamic(this, &UDailyLoginRewardButtonWidget::OnClickAcceptButton);
}

void UDailyLoginRewardButtonWidget::SetRewardInfo(FRewardInfo InRewardInfo)
{
	RewardInfo = InRewardInfo;
	FString DayString = FString::FromInt(RewardInfo.Day);
	FText DayText = FText::FromString(DayString);
	T_Day->SetText(DayText);
	T_ItemName->SetText(FText::FromString(RewardInfo.ItemName));
	Img_ItemThumbnail->SetBrushFromTexture(RewardInfo.ItemThumbnail);
	InitItemData(RewardInfo);
}

void UDailyLoginRewardButtonWidget::InitItemData(FRewardInfo InRewardInfo)
{
	if (InRewardInfo.ItemType == EItemType::ITEM_Consumable)
	{
		ItemData = NewObject<UPotionItemData>();
	}
	else if (InRewardInfo.ItemType == EItemType::ITEM_NoneConsumable)
	{
		ItemData = NewObject<UNoneConsumableItemData>();
	}
	else
	{
		ItemData = NewObject<UItemData>();
	}
	
	ItemData->ItemName = RewardInfo.ItemName;
	ItemData->Thumbnail = RewardInfo.ItemThumbnail;

	ItemData->ItemType = RewardInfo.ItemType;
	ItemData->ConsumableType = RewardInfo.ConsumableType;
	ItemData->NoneConsumableType = RewardInfo.NoneConsumableType;
}

void UDailyLoginRewardButtonWidget::OnClickAcceptButton()
{
	OnRewardButtonClicked.Broadcast(ButtonIndex);

	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		UUIManager* UIManager = PlayerController->GetUIManager();
		if (UIManager)
		{
			UMailData* MailData = NewObject<UMailData>();
			MailData->SetRewardEventMessage();
			MailData->IsInventoryItem = RewardInfo.IsInInventory;
			MailData->Thumbnail = RewardInfo.ItemThumbnail;
			if (nullptr != ItemData) MailData->ItemData = ItemData; 		

			UIManager->AddReceivedMailToMailBox(MailData);
		}
	}
}
