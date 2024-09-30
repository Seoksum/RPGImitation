// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyPlayerController.h"
#include "Managers/UIManager.h"
#include "Items/MailData.h"
#include "Managers/ChatSystem.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "UI/ChatWidget.h"

AMyPlayerController::AMyPlayerController()
{   
    UIManager = CreateDefaultSubobject<UUIManager>(TEXT("UIManger"));
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    bReplicates = true;
    bAlwaysRelevant = true;

    static ConstructorHelpers::FClassFinder<UUserWidget> ChatWidgetClassRef(TEXT("WidgetBlueprint'/Game/Contents/UI/Chat/WBP_ChatWidget.WBP_ChatWidget_C'"));
    if (ChatWidgetClassRef.Succeeded())
    {
        ChatWidgetClass = ChatWidgetClassRef.Class;
        ChatWidget = CreateWidget<UChatWidget>(GetWorld(), ChatWidgetClass);
    }

}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (IsLocalController())  // Ŭ���̾�Ʈ������ UI ����
    {
        if (ChatWidget)
        {
            ChatWidget->AddToViewport();
        }
    }

    InitChatSystem();
}

void AMyPlayerController::InitChatSystem()
{
    if (HasAuthority())  // ���������� ChatSystem�� ����
    {
        ChatSystem = GetWorld()->SpawnActor<AChatSystem>();
        //ChatSystem->SetOwningOwner(PlayerState);
        ChatSystem->SetOwner(this);
    }
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

UUIManager* AMyPlayerController::GetUIManager()
{
    if (UIManager != nullptr) return UIManager;
    return nullptr;
}

AChatSystem* AMyPlayerController::GetChatSystem()
{
    if (ChatSystem != nullptr) return ChatSystem;

    for (TActorIterator<AChatSystem> It(GetWorld()); It; ++It)
    {
        ChatSystem = *It;
        break;
    }

    return ChatSystem;
}