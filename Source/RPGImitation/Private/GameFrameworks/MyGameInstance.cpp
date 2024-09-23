// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameworks/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFrameworks/LoginSaveGame.h"
#include "Kismet/GameplayStatics.h"


UMyGameInstance::UMyGameInstance()
{

}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("MyGameInstance::Init()"));
	LoadLastLoginTime();
	CheckLoginDate();

}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	UE_LOG(LogTemp, Log, TEXT("MyGameInstance::Shutdown()"));
	SaveLastLoginTime();
}

void UMyGameInstance::CheckLoginDate()
{
	FDateTime CurrentDate = FDateTime::Now();
	
	FTimespan TimeDiff = CurrentDate - LastLoginDate;
	if (TimeDiff.GetTotalSeconds() >= 10.f)
	{
		GetReward(); // 보상
		SaveLastLoginTime(); // LastLoginDate 갱신
	}

}

void UMyGameInstance::GetReward()
{
	UE_LOG(LogTemp, Log, TEXT("Get Reward !! "));
}

void UMyGameInstance::LoadLastLoginTime()
{
	ULoginSaveGame* LoginSaveGame = Cast<ULoginSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("LoginSaveSlot"), 0));
	if (LoginSaveGame)
	{
		LastLoginDate = LoginSaveGame->LastLoginTime;
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
