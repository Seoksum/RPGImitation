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
    UI_LVInventory UMETA(DisplayName = "LV_Inventory"),
    UI_SBInventory UMETA(DisplayName = "SB_Inventory"),
    UI_Mail UMETA(DisplayName = "Mail"),
    UI_DailyReward UMETA(DisplayName = "DailyReward"),
    UI_Shop UMETA(DisplayName = "Shop"),
    UI_WinScreen UMETA(DisplayName = "WinScreen"),
    UI_LoseScreen UMETA(DisplayName = "LoseScreen"),
    UI_None      UMETA(DisplayName = "None")
};


UCLASS(Blueprintable, BlueprintType)
class RPGIMITATION_API UUIManager : public UObject
{
	GENERATED_BODY()
	
public:

    UUIManager();


protected: 

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class UItemList* LV_InventoryWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class UScrollBoxInventoryWidget* SB_InventoryWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class UMailListWidget* MailListWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class USendMailListWidget* SendMailListWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class UFullMailWidget* FullMailWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class UDailyLoginRewardWidget* DailyRewardWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
        class UChatWidget* ChatWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
        class UInventoryWidget* InventoryWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
        class UShopItemListWidget* ShopWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UUserWidget* InGameWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    class UCharacterSkillWidget* CharacterSkillWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
        UUserWidget* WinScreenWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
        UUserWidget* LoseScreenWidget;


public:

    // Widget Class 
    UPROPERTY(EditAnywhere, Category = "Widget Class")
    TSubclassOf<class UItemList> LV_InventoryWidgetClass;

    UPROPERTY(EditAnywhere, Category = "Widget Class")
    TSubclassOf<class UScrollBoxInventoryWidget> SB_InventoryWidgetClass;

    UPROPERTY(EditAnywhere, Category = "Widget Class")
    TSubclassOf<class UMailListWidget> MailListWidgetClass;

    UPROPERTY(EditAnywhere, Category = "Widget Class")
    TSubclassOf<class UFullMailWidget> FullMailWidgetClass;

    UPROPERTY(EditAnywhere, Category = "Widget Class")
    TSubclassOf<class UDailyLoginRewardWidget> DailyRewardWidgetClass;

    UPROPERTY(EditAnywhere, Category = "Widget Class")
    TSubclassOf<class UChatWidget> ChatWidgetClass;

    UPROPERTY(EditAnywhere, Category = "Widget Class")
    TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

    UPROPERTY(EditAnywhere, Category = "Widget Class")
    TSubclassOf<class UShopItemListWidget> ShopWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
        TSubclassOf<UUserWidget> WinScreenWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
        TSubclassOf<UUserWidget> LoseScreenWidgetClass;



public:


    UFUNCTION(BlueprintCallable)
    void UpdateUIState(EUIState NewState, bool IsActive);

    void AddMailToLV(class UMailData* InMailData);
    void AddMailToSB(class UMailData* InMailData);

    void AddReceivedMailToMailBox(class UMailData* InMailData);
    void AddMailToSendMailBox(class UMailData* InMailData);

    UChatWidget* GetChatWidget();

    UFUNCTION(BlueprintCallable)
    void SetInGameWidget(UUserWidget* InWidget);

    void StartSkillAttackQ();
    void StartSkillAttackE();
    void StartSkillAttackR();
};
