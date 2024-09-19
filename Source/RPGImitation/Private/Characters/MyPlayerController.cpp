// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyPlayerController.h"
#include "Managers/UIManager.h"

AMyPlayerController::AMyPlayerController()
{
    UIManager = CreateDefaultSubobject<UUIManager>(TEXT("UIManger"));

}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();


}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // 입력 바인딩: 'Tab' 키로 인벤토리 UI를 토글
    InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AMyPlayerController::ToggleInventory);
}

void AMyPlayerController::ToggleInventory()
{
    //UE_LOG(LogTemp, Log, TEXT("ToggleInventory !! "));
    if (UIManager)
    {
        //if (UIManager->GetCurrentUIState() == EUIState::UI_Inventory)
        //{
        //    UIManager->SetUIState(EUIState::UI_None); // UI 숨김
        //}
        //else
        //{
        //    UIManager->SetUIState(EUIState::UI_Inventory); // 인벤토리 UI 표시
        //}

        if (IsInventoryActived)
        {
            //UIManager->SetUIState(EUIState::UI_None);
            UIManager->UpdateUIState(EUIState::UI_Inventory, false);
        }
        else
        {
            //UIManager->SetUIState(EUIState::UI_Inventory); 
            UIManager->UpdateUIState(EUIState::UI_Inventory, true);
        }
        IsInventoryActived = !IsInventoryActived;
    }
}