// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UChatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

    virtual void NativeConstruct() override;
	
public:

    UPROPERTY(meta = (BindWidget))
    class UEditableText* ET_ChatBox;

    UPROPERTY(meta = (BindWidget))
        class UButton* Btn_Send;

    UPROPERTY(meta = (BindWidget))
        class UScrollBox* SB_ChatLog;

    UFUNCTION()
    void OnSendMessage(const FText& Text, ETextCommit::Type CommitMethod);

    UFUNCTION()
    void OnChatMessageReceived(const FString& Message);

    void AppendLogToChatBox(const FString& Message);


};
