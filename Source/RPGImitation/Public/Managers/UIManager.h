// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIManager.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EUIState : uint8
{
    UI_Inventory UMETA(DisplayName = "Inventory"),
    UI_SBInventory UMETA(DisplayName = "SB_Inventory"),
    UI_Mail UMETA(DisplayName = "Mail"),
    UI_DailyReward UMETA(DisplayName = "DailyReward"),
    UI_None      UMETA(DisplayName = "None")
};


UCLASS(Blueprintable, BlueprintType)
class RPGIMITATION_API UUIManager : public UObject
{
	GENERATED_BODY()
	
public:

    UUIManager();

    UUserWidget* CurrentWidget;

    EUIState CurrentUIState;


protected: 

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class UItemList* InventoryWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class UScrollBoxInventoryWidget* SB_InventoryWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class UMailListWidget* MailListWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
        class UFullMailWidget* FullMailWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
        class UDailyLoginRewardWidget* DailyRewardWidget;

public:

    // Widget Class 
    UPROPERTY(EditAnywhere, Category = "Widget Class")
    TSubclassOf<class UItemList> InventoryWidgetClass;

    UPROPERTY(EditAnywhere, Category = "Widget Class")
    TSubclassOf<class UScrollBoxInventoryWidget> SB_InventoryWidgetClass;

    UPROPERTY(EditAnywhere, Category = "Widget Class")
    TSubclassOf<class UMailListWidget> MailListWidgetClass;

    UPROPERTY(EditAnywhere, Category = "Widget Class")
    TSubclassOf<class UFullMailWidget> FullMailWidgetClass;

    UPROPERTY(EditAnywhere, Category = "Widget Class")
        TSubclassOf<class UDailyLoginRewardWidget> DailyRewardWidgetClass;



public:

    // UI ���¸� �����ϴ� �Լ�
    void SetUIState(EUIState NewState);

    // ���� ���¿� ���� UI ǥ��
    void UpdateUI();

    UFUNCTION(BlueprintCallable)
    void UpdateUIState(EUIState NewState, bool IsActive);

    EUIState GetCurrentUIState();

    void AddItemToInventory(class AItem* InItem);
    void SB_AddItemToInventory(class AItem* InItem);
    void AddMailToMailBox(class UMailData* InMailData);


};
