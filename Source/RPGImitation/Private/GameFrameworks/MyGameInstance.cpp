// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameworks/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFrameworks/LoginSaveGame.h"
#include "Kismet/GameplayStatics.h"


UMyGameInstance::UMyGameInstance()
{
	FString RewardDataPath = TEXT("DataTable'/Game/Contents/Data/RewardDataTable.RewardDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> RewardDataPathObject(*RewardDataPath);
	if (RewardDataPathObject.Succeeded())
	{
		RewardDataTable = RewardDataPathObject.Object;
	}

	UpdateTime = 5.f;
}

void UMyGameInstance::Init()
{
	Super::Init();

	
	LoadLastLoginTime();
	CheckLoginDate();

}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();


	SaveLastLoginTime();
}

bool UMyGameInstance::CheckLoginDate()
{
	FDateTime CurrentDate = FDateTime::Now();
	
	FTimespan TimeDiff = CurrentDate - LastLoginDate;
	if (TimeDiff.GetTotalSeconds() >= UpdateTime)
	{
		GetReward(); // 보상
		SaveLastLoginTime(); // LastLoginDate 갱신
		return true;
	}
	return false;
}

void UMyGameInstance::GetReward()
{
	UE_LOG(LogTemp, Log, TEXT("Get Reward !! "));
}

void UMyGameInstance::LoadLastLoginTime()
{
	ULoginSaveGame* LoginSaveGame = Cast<ULoginSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("LoginSaveSlot"), 0));
	if (LoginSaveGame)
	{		LastLoginDate = LoginSaveGame->LastLoginTime;
	}
}

void UMyGameInstance::SaveLastLoginTime()
{
	LastLoginDate = FDateTime::Now();

	ULoginSaveGame* LoginSaveGame = Cast<ULoginSaveGame>(UGameplayStatics::CreateSaveGameObject(ULoginSaveGame::StaticClass()));
	if (LoginSaveGame)
	{
		LoginSaveGame->LastLoginTime = LastLoginDate;
		UGameplayStatics::SaveGameToSlot(LoginSaveGame, TEXT("LoginSaveSlot"), 0);
	}
}

FRewardDataTable* UMyGameInstance::GetRewardDataTable(int32 Day)
{
	return RewardDataTable->FindRow<FRewardDataTable>(*FString::FromInt(Day), TEXT(""));
}

