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

	UFUNCTION(BlueprintCallable)
	void ClickDeleteMailButton();

	UFUNCTION()
	void ChangeAllMailCheckBox(bool IsChecked);

public:

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_ReceiveMail;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_SendMail;

	UPROPERTY(meta = (BindWidget))
	class UMailListWidget* WBP_MailListWidget;

	UPROPERTY(meta = (BindWidget))
	class USendMailListWidget* WBP_SendMailListWidget;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_DeleteMail;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* CB_CheckAllMail;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
		class UWidgetSwitcher* WS_Mail;


};
