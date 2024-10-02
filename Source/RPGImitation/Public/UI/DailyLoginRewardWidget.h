// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/RewardDataTable.h"
#include "DailyLoginRewardWidget.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FRewardInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 Index; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 Day; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UTexture2D* ItemThumbnail;
};

UCLASS()
class RPGIMITATION_API UDailyLoginRewardWidget : public UUserWidget
{
	GENERATED_BODY()

public:

    virtual void NativeConstruct() override;
    virtual void NativeOnInitialized() override;
    virtual void NativeDestruct() override;

    void CreateRewardInfos();

    void InitGridPanel();

    void OnClickButton(int32 ButtonIndex);
	
protected:

    UPROPERTY(BlueprintReadOnly)
    TArray<FRewardInfo> RewardInfos;

    UPROPERTY(BlueprintReadOnly)
    FRewardDataTable RewardDataTable;

    UPROPERTY(BlueprintReadWrite)
    int32 ItemCount;

    UPROPERTY(BlueprintReadWrite)
        int32 RowSize;

    UPROPERTY(BlueprintReadWrite)
        int32 ColSize;


    UPROPERTY(VisibleAnywhere)
        bool IsButtonCreated = false;


public:

    UPROPERTY()
    class ULoginSaveGame* SaveLoginSaveGame;

    UPROPERTY(meta = (BindWidget))
    class UGridPanel* GP_Reward;

    UPROPERTY(EditAnywhere, Category = "UI")
    class UDailyLoginRewardButtonWidget* ButtonWidget;

    // 위젯 클래스 참조
    UPROPERTY(BlueprintReadWrite, Category = "UI", Meta = (BlueprintProtected = true))
    TSubclassOf<class UDailyLoginRewardButtonWidget> ButtonWidgetClass;

    UPROPERTY(BlueprintReadOnly, Category = "Game")
    TArray<class UDailyLoginRewardButtonWidget*> ButtonWidgetArray;

    UPROPERTY(BlueprintReadOnly, Category = "Game")
    class UMyGameInstance* GameInstance;

    FTimerHandle CheckLoginTimerHandle;

    UPROPERTY(EditAnywhere,Category="Timer")
    float LifeSpan;
  

    void SetActiveNextButton(int32 NextButtonIndex);

};
