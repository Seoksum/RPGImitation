// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ChatWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Managers/ChatSystem.h"
#include "Characters/MyPlayerController.h"

void UChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ET_ChatBox->OnTextCommitted.AddDynamic(this, &UChatWidget::OnSendMessage);

	AMyPlayerController* PC = Cast<AMyPlayerController>(GetOwningPlayer());
	if (PC)
	{
		AChatSystem* ChatSystem = PC->GetChatSystem();
		if (ChatSystem)
		{
			ChatSystem->OnMessageReceived.AddUObject(this, &UChatWidget::OnChatMessageReceived);
		}
	}
}

void UChatWidget::OnSendMessage(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		UE_LOG(LogTemp, Log, TEXT("Send Message Enter !"));
		FString Message = Text.ToString();
		AMyPlayerController* PC = Cast<AMyPlayerController>(GetOwningPlayer());
		if (PC)
		{
			AChatSystem* ChatSystem = PC->GetChatSystem();
			if (ChatSystem)
			{
				ChatSystem->ServerSendMessage(Message);
				ET_ChatBox->SetText(FText::GetEmpty());
			}
				
		}
	}
}

void UChatWidget::OnChatMessageReceived(const FString& Message)
{
	AppendLogToChatBox(Message);
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
