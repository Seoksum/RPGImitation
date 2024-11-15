// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SendMailWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API USendMailWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

public:

	void SetMailInfo(class UMailData* InMail);

	UFUNCTION()
	void OnClickMailMessage();

	FORCEINLINE void SetIsInViewportNow(bool InViewport) { IsInViewportNow = InViewport; }

public:

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_MailMessage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_Sender;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_Title;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* CB_MailSelected;



protected:

	// 위젯 클래스 참조
	UPROPERTY(BlueprintReadWrite, Category = "UI", Meta = (BlueprintProtected = true))
	TSubclassOf<class USentPostalWidget> SentPostalWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	class UMailData* SendMail;

	UPROPERTY(BlueprintReadOnly)
	bool IsInViewportNow;

	UPROPERTY(BlueprintReadWrite)
	bool IsInventoryItem;

};
