// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Managers/UIManager.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

    AMyPlayerController();

    UFUNCTION(BlueprintCallable)
    UUIManager* GetUIManager();

    UFUNCTION(BlueprintCallable)
    class AChatSystem* GetChatSystem();

protected:

    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override; 

    virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

protected:

    // UI 상태 변경 함수
    void LVToggleInventory();

    void SBToggleInventory();

    void Cheat_Mail();

    void Cheat_Gold();

    void InitChatSystem();

    void ToggleInventory();

public:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
        class UChatWidget* ChatWidget;

    UPROPERTY(EditAnywhere, Category = "Widget Class")
        TSubclassOf<class UChatWidget> ChatWidgetClass;


private:

    UPROPERTY()
        class UUIManager* UIManager;

    UPROPERTY()
        class AChatSystem* ChatSystem;

    UPROPERTY(VisibleAnywhere)
        bool IsInventoryActived;

    UPROPERTY(VisibleAnywhere)
    bool SBIsInventoryActived;

};
