// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ChatWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Managers/ChatSystem.h"
#include "Characters/MyPlayerController.h"
#include "Managers/UIManager.h"
#include "Kismet/GameplayStatics.h"

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
			UE_LOG(LogTemp, Warning, TEXT("Chatsystem is not nullptr"));
			ChatSystem->OnMessageReceived.AddUObject(this, &UChatWidget::OnChatMessageReceived);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Chatsystem is nullptr TT"));
		}
	}
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
				AppendLogToChatBox(Message);
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
		UE_LOG(LogTemp, Warning, TEXT("[ChatWidget] AppendLogToChatBox added message: %s"), *Message);

		SB_ChatLog->ScrollToEnd();

	}
}


