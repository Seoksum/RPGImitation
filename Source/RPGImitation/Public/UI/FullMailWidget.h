// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FullMailWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UFullMailWidget : public UUserWidget
{
	GENERATED_BODY()
	


public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void ClickReceiveMailButton();

	UFUNCTION()
		void ClickSendMailButton();


public:

	UPROPERTY(meta = (BindWidget))
		class UButton* Btn_ReceiveMail;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_SendMail;

	UPROPERTY(meta = (BindWidget))
	class UMailListWidget* WBP_MailListWidget;

};
