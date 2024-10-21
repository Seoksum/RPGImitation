// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "MailWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UMailWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

public:

	void SetMailInfo(class UMailData* InMail);

	UFUNCTION()
	void OnClickReceivedMailMessage();

	UFUNCTION()
	void OnClickReceiveItemButton();

	FORCEINLINE void SetIsInViewportNow(bool InViewport) { IsInViewportNow = InViewport; }
	FORCEINLINE void SetIsInventoryItem(bool bIsInventoryItem) { IsInventoryItem = bIsInventoryItem; }

public:

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_MailMessage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_Sender;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_Title;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* CB_MailSelected;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CP_Item;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Item;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_ReceiveItem;

protected:

	// 위젯 클래스 참조
	UPROPERTY(BlueprintReadWrite, Category = "Mail", Meta = (BlueprintProtected = true))
	TSubclassOf<class UReceivePostalWidget> ReceivePostalWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Mail")
	class UMailData* ReceiveMail;

	UPROPERTY(BlueprintReadOnly)
	bool IsInViewportNow;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool IsInventoryItem;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Characters")
	class ARPGImitationCharacter* Character;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Characters")
	class UInventoryComponent* Inventory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Reward")
		int32 RewardGold;



};
