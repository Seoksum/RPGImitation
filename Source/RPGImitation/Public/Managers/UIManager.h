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
    UI_None      UMETA(DisplayName = "None")
};


UCLASS(Blueprintable, BlueprintType)
class RPGIMITATION_API UUIManager : public UObject
{
	GENERATED_BODY()
	
public:

    UUIManager();

    // ���� UI ����
    UUserWidget* CurrentWidget;

    // UI Enum
    EUIState CurrentUIState;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UItemList* InventoryWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UScrollBoxInventoryWidget* SB_InventoryWidget;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UMailListWidget* MailListWidget;

    UPROPERTY(EditAnywhere, Category = "UI")
        class UFullMailWidget* FullMailWidget;

    // ���� Ŭ���� ����
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UItemList> InventoryWidgetClass;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UScrollBoxInventoryWidget> SB_InventoryWidgetClass;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UMailListWidget> MailListWidgetClass;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UFullMailWidget> FullMailWidgetClass;



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
