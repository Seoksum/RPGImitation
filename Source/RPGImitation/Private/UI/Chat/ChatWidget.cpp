// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Chat/ChatWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Components/HorizontalBox.h"
#include "Managers/ChatSystem.h"
#include "Characters/MyPlayerController.h"
#include "Managers/UIManager.h"
#include "Kismet/GameplayStatics.h"

void UChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ET_ChatBox->OnTextCommitted.AddDynamic(this, &UChatWidget::OnSendMessage);
	Btn_Send->OnClicked.AddDynamic(this, &UChatWidget::OnClickSendButton);
	Btn_DownScrollBox->OnClicked.AddDynamic(this, &UChatWidget::OnClickDownScrollBox);
	Btn_UpScrollBox->OnClicked.AddDynamic(this, &UChatWidget::OnClickUpScrollBox);
}

void UChatWidget::OnSendMessage(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		FString Message = Text.ToString();
		AMyPlayerController* PC = Cast<AMyPlayerController>(GetOwningPlayer());
		if (PC)
		{
			AChatSystem* ChatSystem = PC->GetChatSystem();
			if (ChatSystem)
			{
				ChatSystem->ServerSendMessage(Message);
				ET_ChatBox->SetText(FText::GetEmpty());
				//AppendLogToChatBox(Message);
			}				
		}
	}
}

void UChatWidget::AppendLogToChatBox(const FString& Message)
{
	UTextBlock* NewMessage = NewObject<UTextBlock>(SB_ChatLog);
	if (NewMessage)
	{
		NewMessage->SetText(FText::FromString(Message));
		SB_ChatLog->AddChild(NewMessage);
		SB_ChatLog->ScrollToEnd();
	}
}

void UChatWidget::OnClickSendButton()
{
	OnSendMessage(ET_ChatBox->GetText(), ETextCommit::OnEnter);
}

void UChatWidget::OnClickDownScrollBox()
{
	ChatPanel->SetVisibility(ESlateVisibility::Collapsed);
	HB_ChatLog->SetRenderTranslation(FVector2D(0.f, 400.f));
}

void UChatWidget::OnClickUpScrollBox()
{
	//if (SB_ChatLog->GetVisibility() == ESlateVisibility::Collapsed)
	ChatPanel->SetVisibility(ESlateVisibility::Visible);
	HB_ChatLog->SetRenderTranslation(FVector2D(0.f, 0.f));
}


