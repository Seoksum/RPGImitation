// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameworks/MyGameModeBase.h"
#include "Characters/MyPlayerController.h"
#include "AI/AIController_Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "GameFrameworks/MyGameInstance.h"
#include "../RPGImitationCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<ARPGImitationCharacter> BPCharacterPath(TEXT("Blueprint'/Game/Contents/Blueprints/Characters/PlayerCharacter/BP_MyRPGCharacter.BP_MyRPGCharacter_C'"));
	if (BPCharacterPath.Succeeded())
	{
		DefaultPawnClass = BPCharacterPath.Class;
	}


}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		APawn* DefaultPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (DefaultPawn)
		{
			USkeletalMeshComponent* SkeletalMeshComponent = DefaultPawn->FindComponentByClass<USkeletalMeshComponent>();
			if (SkeletalMeshComponent)
			{
				USkeletalMesh* SelectedSkeletalMesh = MyGameInstance->GetSelectedSkeletalMesh();
				if (SelectedSkeletalMesh)
				{
					SkeletalMeshComponent->SetSkeletalMesh(SelectedSkeletalMesh);
				}
			}
		}
	}
}

void AMyGameModeBase::IncreaseExp(AController* KillerController, float Exp)
{
	ARPGImitationCharacter* PlayerCharacter = Cast<ARPGImitationCharacter>(KillerController->GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->IncreaseExp(Exp);
	}
}


void AMyGameModeBase::PawnKilled(class APawn* PawnKilled)
{
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{
		EndGame(false); // Player�� ���� ���
	}

	for (AAIController_Enemy* Controller : TActorRange<AAIController_Enemy>(GetWorld()))
	{
		if (!Controller->IsEnemyAIDead())
		{
			return; // ���� �������� �׾��ִ� AI�� ���ٸ� ���� return 
		}
	}

	EndGame(true); // ���� Ȯ�� �� �� �׾��ִٸ� Player �¸�
}

void AMyGameModeBase::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}