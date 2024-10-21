// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SendPostalWidget.generated.h"

/**
 *
 */
UCLASS()
class RPGIMITATION_API USendPostalWidget : public UUserWidget
{
	GENERATED_BODY()


protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnClickSendButton();


public:

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
		class UEditableText* ET_ReceiverName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UEditableText* ET_Contents;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UEditableText* ET_Title;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Btn_Send;

protected:

	void SetInitialState();

};
