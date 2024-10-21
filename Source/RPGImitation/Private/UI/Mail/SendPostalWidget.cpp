// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mail/SendPostalWidget.h"
#include "Items/MailData.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/EditableText.h"
#include "Items/MailData.h"
#include "Managers/UIManager.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/MyPlayerController.h"


void USendPostalWidget::NativeConstruct()
{
	Super::NativeConstruct();


	Btn_Send->OnClicked.RemoveDynamic(this, &USendPostalWidget::OnClickSendButton);
	Btn_Send->OnClicked.AddDynamic(this, &USendPostalWidget::OnClickSendButton);


}

void USendPostalWidget::OnClickSendButton()
{
	// 메일 저장, 메일 보내기 
	UMailData* MailData = NewObject<UMailData>();
	MailData->Receiver = ET_ReceiverName->GetText().ToString();
	MailData->Title = ET_Title->GetText().ToString();
	MailData->Message = ET_Contents->GetText().ToString();

	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UUIManager* UIManager = PlayerController->GetUIManager();
	if (UIManager)
	{
		UIManager->AddMailToSendMailBox(MailData);
	}
	SetInitialState();
}

void USendPostalWidget::SetInitialState()
{
	FString str = "";
	FText InText = FText::FromString(str);
	ET_ReceiverName->SetText(InText);
	ET_Title->SetText(InText);
	ET_Contents->SetText(InText);
}