// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameworks/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFrameworks/LoginSaveGame.h"


UMyGameInstance::UMyGameInstance()
{
	FString RewardDataPath = TEXT("DataTable'/Game/Contents/Data/RewardDataTable.RewardDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> RewardDataPathObject(*RewardDataPath);
	if (RewardDataPathObject.Succeeded())
	{
		RewardDataTable = RewardDataPathObject.Object;
	}

	FString ShopItemDataPath = TEXT("DataTable'/Game/Contents/Data/ShopItemDataTable.ShopItemDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> ShopItemDataPathObject(*ShopItemDataPath);
	if (ShopItemDataPathObject.Succeeded())
	{
		ShopItemDataTable = ShopItemDataPathObject.Object;
	}

	UpdateTime = 1.f;
}

void UMyGameInstance::Init()
{
	Super::Init();

	LoadLastRewardTime();
	CheckRewardDate();

}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	SaveLastRewardTime();
}

bool UMyGameInstance::CheckRewardDate()
{
	FDateTime CurrentDate = FDateTime::Now();
	FTimespan TimeDiff = CurrentDate - LastRewardDate;

	if (TimeDiff.GetTotalSeconds() >= UpdateTime)
	{
		SaveLastRewardTime(); // LastRewardDate °»½Å
		return true;
	}
	return false;
}

void UMyGameInstance::GetReward()
{
	//UE_LOG(LogTemp, Log, TEXT("Get Reward !! "));
}

void UMyGameInstance::LoadLastRewardTime()
{
	ULoginSaveGame* LoginSaveGame = Cast<ULoginSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("LoginSaveSlot"), 0));
	if (LoginSaveGame)
	{		
		LastRewardDate = LoginSaveGame->LastRewardTime;
	}
}

void UMyGameInstance::SaveLastRewardTime()
{
	LastRewardDate = FDateTime::Now();

	ULoginSaveGame* LoginSaveGame = Cast<ULoginSaveGame>(UGameplayStatics::CreateSaveGameObject(ULoginSaveGame::StaticClass()));
	if (LoginSaveGame)
	{
		LoginSaveGame->LastRewardTime = LastRewardDate;
		UGameplayStatics::SaveGameToSlot(LoginSaveGame, TEXT("LoginSaveSlot"), 0);
	}
}

FRewardDataTable* UMyGameInstance::GetRewardDataTable(int32 Day)
{
	return RewardDataTable->FindRow<FRewardDataTable>(*FString::FromInt(Day), TEXT(""));
}

FShopItemDataTable* UMyGameInstance::GetShopItemDataTable(int32 Index)
{
	return ShopItemDataTable->FindRow<FShopItemDataTable>(*FString::FromInt(Index), TEXT(""));
}

float UMyGameInstance::GetUpdateTime()
{
	return UpdateTime;
}

