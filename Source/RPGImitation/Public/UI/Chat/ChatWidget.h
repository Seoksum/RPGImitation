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

    UFUNCTION()
    void OnSendMessage(const FText& Text, ETextCommit::Type CommitMethod);

    void AppendLogToChatBox(const FString& Message);

    UFUNCTION()
    void OnClickSendButton();

    UFUNCTION()
        void OnClickDownScrollBox();

    UFUNCTION()
        void OnClickUpScrollBox();

protected:

    UPROPERTY(meta = (BindWidget))
        class UPanelWidget* ChatPanel;

    UPROPERTY(meta = (BindWidget))
    class UEditableText* ET_ChatBox;

    UPROPERTY(meta = (BindWidget))
        class UButton* Btn_Send;

    UPROPERTY(meta = (BindWidget))
        class UScrollBox* SB_ChatLog;

    UPROPERTY(meta = (BindWidget))
        class UButton* Btn_DownScrollBox;

    UPROPERTY(meta = (BindWidget))
        class UButton* Btn_UpScrollBox;

    UPROPERTY(meta = (BindWidget))
        class UHorizontalBox* HB_ChatLog;



    bool bIsMovingDown = false;
    bool bIsMovingUp = false;

    float CurrentOffset = 0.0f;
    float MaxOffset = 300.0f;  // 채팅창을 내리는 최대 오프셋 값

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
        float AnimationSpeed = 300.0f;  // 초당 300 유닛 이동

};
