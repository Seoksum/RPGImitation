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
	
	// �⼮������ 3�� ������ ���� ������ ���ϵ� 3���� �� 
	// => �⼮üũ������ Ŭ���� ��� UDailyLoginRewardWidget�� �����µ� Ŭ�� �� ������ �⼮üũ�ϼ��� �ö󰡴� �� ����
	// ���ϵ� �׸�ŭ ��
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
