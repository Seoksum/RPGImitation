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

	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterStatDataTable(TEXT("DataTable'/Game/Contents/Data/CharacterStatDataTable.CharacterStatDataTable'"));

	if (CharacterStatDataTable.Object)
	{
		const UDataTable* StatDataTable = CharacterStatDataTable.Object;

		TArray<FStatDataTable*> CharacterStats;
		StatDataTable->GetAllRows<FStatDataTable>(TEXT("GetAllRows"), CharacterStats);
		for (int32 i = 0; i < CharacterStats.Num(); ++i)
		{
			CharacterStatTables.Add(*CharacterStats[i]);
		}
	}
	MaxLevel = CharacterStatTables.Num();

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

void UMyGameInstance::SetCharacterMeshIndex(USkeletalMesh* SelectedSkeletalMesh)
{
	CharacterSkeletalMesh = SelectedSkeletalMesh;
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

FStatDataTable UMyGameInstance::GetCharacterStat(int32 Level)
{
	if (Level >= 1 && Level < MaxLevel)
	{
		return CharacterStatTables[Level - 1];
	}
	return FStatDataTable();
	//return *StatDataTable->FindRow<FStatDataTable>(*FString::FromInt(Level), TEXT(""));
}


float UMyGameInstance::GetUpdateTime()
{
	return UpdateTime;
}

USkeletalMesh* UMyGameInstance::GetSelectedSkeletalMesh()
{
	return CharacterSkeletalMesh;
}


