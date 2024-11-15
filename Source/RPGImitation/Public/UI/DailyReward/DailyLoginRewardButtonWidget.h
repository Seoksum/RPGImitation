// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/DailyReward/DailyLoginRewardWidget.h"
#include "DailyLoginRewardButtonWidget.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRewardButtonClicked,int32);

UCLASS()
class RPGIMITATION_API UDailyLoginRewardButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void SetRewardInfo(FRewardInfo InRewardInfo);

	FOnRewardButtonClicked OnRewardButtonClicked;


protected:

	UFUNCTION()
	void OnClickAcceptButton();

	FRewardInfo RewardInfo;

	void InitItemData(FRewardInfo InRewardInfo);


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ButtonIndex")
	int32 ButtonIndex;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_AcceptItem;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_ItemName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_Day;

	UPROPERTY(meta = (BindWidget))
		class UImage* Img_ItemThumbnail;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
	class UItemData* ItemData;



};
