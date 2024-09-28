// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DailyLoginRewardButtonWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFrameworks/LoginSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "UI/DailyLoginRewardWidget.h"
#include "Items/MailData.h"
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
			MailData->IsInventoryItem = true;
			MailData->ItemImage = RewardInfo.ItemThumbnail;
			UIManager->AddMailReceiveToMailBox(MailData);
		}
	}

}
