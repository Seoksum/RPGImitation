// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DailyLoginRewardWidget.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FRewardInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 DayNumber;  // 몇 번째 날인지

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString RewardDescription;  // 보상 설명

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UTexture2D* RewardThumbnail;  // 보상 아이콘
};

UCLASS()
class RPGIMITATION_API UDailyLoginRewardWidget : public UUserWidget
{
	GENERATED_BODY()

public:

    void CreateDailyLoginRewardInfo();

	
protected:

    UPROPERTY(meta = (BindWidget))
    class UGridPanel* GP_Reward;

    TArray<FRewardInfo> RewardInfo;


};
