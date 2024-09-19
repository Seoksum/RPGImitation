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
    UI_Map       UMETA(DisplayName = "Map"),
    UI_MainMenu  UMETA(DisplayName = "MainMenu"),
    UI_None      UMETA(DisplayName = "None")
};


UCLASS()
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

    // ���� Ŭ���� ����
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UItemList> InventoryWidgetClass;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> MapWidgetClass;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> MainMenuWidgetClass;

    // UI ���¸� �����ϴ� �Լ�
    void SetUIState(EUIState NewState);

    // ���� ���¿� ���� UI ǥ��
    void UpdateUI();
    void UpdateUIState(EUIState NewState, bool IsActive);

    EUIState GetCurrentUIState();

    void AddItemToInventory(class AItem* InItem);


protected:

    void ShowListWidget();


};
