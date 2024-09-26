// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SentPostalWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API USentPostalWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnClickCloseButton();

public: 

	void  SetMailInfo(class UMailData* InMailData);


protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T_ReceiverName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T_Title;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* T_Contents;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* Btn_Close;

};
