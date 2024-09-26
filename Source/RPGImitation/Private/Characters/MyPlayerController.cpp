// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyPlayerController.h"
#include "Managers/UIManager.h"
#include "Items/MailData.h"

AMyPlayerController::AMyPlayerController()
{
    UIManager = CreateDefaultSubobject<UUIManager>(TEXT("UIManger"));

}

UUIManager* AMyPlayerController::GetUIManager()
{
    if(UIManager!=nullptr) return UIManager;
    return nullptr;
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
    InputComponent->BindAction("SBToggleInventory", IE_Pressed, this, &AMyPlayerController::SBToggleInventory);

    InputComponent->BindAction("MyCheat", IE_Pressed, this, &AMyPlayerController::EnableMyCheat);

    // �ܼ� ��ɾ�� ���ε��� �Լ�
    if (GEngine)
    {
        GEngine->Exec(GetWorld(), TEXT("MyCheat"));
    }
}

void AMyPlayerController::EnableMyCheat()
{
    if (GEngine)
    {
        UMailData* MailData = NewObject<UMailData>();
        MailData->Sender = "Cheat";
        MailData->Title = "Cheat Title";
        MailData->Message = "Test Message...";

        UIManager->AddMailReceiveToMailBox(MailData);
        if (GEngine)
        {
            GEngine->Exec(GetWorld(), TEXT("MyCheat"));
        }
    }
}


void AMyPlayerController::ToggleInventory()
{
    if (UIManager)
    {
        if (IsInventoryActived)
        {
            SetInputMode(FInputModeGameOnly());
        }
        else
        {
            SetInputMode(FInputModeGameAndUI());
        }

        IsInventoryActived = !IsInventoryActived;
        UIManager->UpdateUIState(EUIState::UI_Inventory, IsInventoryActived);
        bShowMouseCursor = IsInventoryActived;
    }
}

void AMyPlayerController::SBToggleInventory()
{
    if (UIManager)
    {
        if (SBIsInventoryActived)
        {
            //UIManager->UpdateUIState(EUIState::UI_SBInventory, false);
            SetInputMode(FInputModeGameOnly());
        }
        else
        {
            //UIManager->UpdateUIState(EUIState::UI_SBInventory, true);
            SetInputMode(FInputModeGameAndUI());
        }
        SBIsInventoryActived = !SBIsInventoryActived;
        UIManager->UpdateUIState(EUIState::UI_SBInventory, SBIsInventoryActived);
        bShowMouseCursor = SBIsInventoryActived;
    }
}