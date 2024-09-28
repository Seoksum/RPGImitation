// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyPlayerController.h"
#include "Managers/UIManager.h"
#include "Items/MailData.h"
#include "Managers/ChatSystem.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerController::AMyPlayerController()
{   
    UIManager = CreateDefaultSubobject<UUIManager>(TEXT("UIManger"));
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    bReplicates = true;
    bAlwaysRelevant = true;
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    InitChatSystem();
}

void AMyPlayerController::InitChatSystem()
{
    if (HasAuthority())  // 서버에서만 ChatSystem을 생성
    {
        ChatSystem = GetWorld()->SpawnActor<AChatSystem>();
        ChatSystem->SetOwningOwner(GetPawn());
        ChatSystem->SetOwner(GetPawn());

        if (nullptr != GetPawn())
        {
            UE_LOG(LogTemp, Warning, TEXT("ChatSystem owner is set to Pawn: %s"), *GetPawn()->GetName());
        }
    }
}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // 입력 바인딩: 'Tab' 키로 인벤토리 UI를 토글
    InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AMyPlayerController::ToggleInventory);
    InputComponent->BindAction("SBToggleInventory", IE_Pressed, this, &AMyPlayerController::SBToggleInventory);

    InputComponent->BindAction("MyCheat", IE_Pressed, this, &AMyPlayerController::EnableMyCheat);

    // 콘솔 명령어와 바인딩된 함수
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