// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyPlayerController.h"
#include "Managers/UIManager.h"
#include "Items/MailData.h"
#include "Managers/ChatSystem.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Chat/ChatWidget.h"
#include "../RPGImitationCharacter.h"

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

	InitChatSystem();

	if (IsLocalController())  // 클라이언트에서만 UI 생성
	{
		if (ChatWidget)
		{
			ChatWidget->AddToViewport();
		}
	}
}

void AMyPlayerController::InitChatSystem()
{
	if (HasAuthority())  // 서버에서만 ChatSystem을 생성
	{
		ChatSystem = GetWorld()->SpawnActor<AChatSystem>();
		ChatSystem->SetOwner(this);
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 입력 바인딩: 'Tab' 키로 인벤토리 UI를 토글
	//InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AMyPlayerController::LVToggleInventory);
	//InputComponent->BindAction("SBToggleInventory", IE_Pressed, this, &AMyPlayerController::SBToggleInventory);
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AMyPlayerController::ToggleInventory);

	InputComponent->BindAction("MailCheat", IE_Pressed, this, &AMyPlayerController::Cheat_Mail);
	InputComponent->BindAction("GoldCheat", IE_Pressed, this, &AMyPlayerController::Cheat_Gold);

	// 콘솔 명령어와 바인딩된 함수
	if (GEngine)
	{
		GEngine->Exec(GetWorld(), TEXT("MyCheat"));
	}
}

void AMyPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner)
	{
		UIManager->UpdateUIState(EUIState::UI_WinScreen, true);
	}
	else
	{
		UIManager->UpdateUIState(EUIState::UI_LoseScreen, true);
	}
}


void AMyPlayerController::Cheat_Mail()
{
	if (GEngine)
	{
		UMailData* MailData = NewObject<UMailData>();
		MailData->Sender = "Cheat";
		MailData->Title = "Cheat Title";
		MailData->Message = "Test Message...";

		UIManager->AddReceivedMailToMailBox(MailData);
	}
}

void AMyPlayerController::Cheat_Gold()
{
	ARPGImitationCharacter* MyCharacter = Cast<ARPGImitationCharacter>(GetPawn());
	if (MyCharacter)
	{
		MyCharacter->AddGold(10000);
	}
}

void AMyPlayerController::ToggleInventory()
{
	if (UIManager)
	{
		SetInputMode(FInputModeGameAndUI());
		IsInventoryActived = !IsInventoryActived;
		UIManager->UpdateUIState(EUIState::UI_Inventory, IsInventoryActived);
	}

}

void AMyPlayerController::LVToggleInventory()
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
		UIManager->UpdateUIState(EUIState::UI_LVInventory, IsInventoryActived);
		bShowMouseCursor = IsInventoryActived;
	}
}

void AMyPlayerController::SBToggleInventory()
{
	if (UIManager)
	{
		if (SBIsInventoryActived)
		{
			SetInputMode(FInputModeGameOnly());
		}
		else
		{
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