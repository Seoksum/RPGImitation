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

    // UIManager 인스턴스를 관리할 변수
    UPROPERTY()
    class UUIManager* UIManager;

protected:

    virtual void BeginPlay() override;

    virtual void SetupInputComponent() override; 

    // UI 상태 변경 함수
    void ToggleInventory();

    void SBToggleInventory();

    void EnableMyCheat();

private:

    UPROPERTY(VisibleAnywhere)
        bool IsInventoryActived;

    UPROPERTY(VisibleAnywhere)
    bool SBIsInventoryActived;

};
