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

    // �Է� ���ε�: 'Tab' Ű�� �κ��丮 UI�� ���
    InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AMyPlayerController::ToggleInventory);
}

void AMyPlayerController::ToggleInventory()
{
    //UE_LOG(LogTemp, Log, TEXT("ToggleInventory !! "));
    if (UIManager)
    {
        //if (UIManager->GetCurrentUIState() == EUIState::UI_Inventory)
        //{
        //    UIManager->SetUIState(EUIState::UI_None); // UI ����
        //}
        //else
        //{
        //    UIManager->SetUIState(EUIState::UI_Inventory); // �κ��丮 UI ǥ��
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