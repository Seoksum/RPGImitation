// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterSelection.h"
#include "Kismet/GameplayStatics.h"
//#include "GameFrameworks/CharacterSelectController.h"

// Sets default values
ACharacterSelection::ACharacterSelection()
{
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootScene;

	// Greystone
	CharacterSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("CharacterScene"));
	CharacterSceneComp->SetupAttachment(RootComponent);
	for (int32 i = 1; i <= 4; i++)
	{
		class USkeletalMeshComponent* MurielSkeletalMesh;
		FString FormattedNum = FString::Printf(TEXT("Character%d"), i);
		MurielSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>((TEXT("%s"), *FormattedNum), false);
		MurielSkeletalMesh->SetupAttachment(CharacterSceneComp);
		MurielSkeletalMesh->SetVisibility(false);
		CharacterMeshArray.Add(MurielSkeletalMesh);
	}
}

// Called when the game starts or when spawned
void ACharacterSelection::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterMeshArray[0]->SetVisibility(true);
}

void ACharacterSelection::NextOrBefore(bool IsNext)
{
	CharacterMeshArray[CharacterMeshIdx]->SetVisibility(false);
	if (IsNext) 
	{ 
		CharacterMeshIdx = (CharacterMeshIdx + 1) % CharacterMeshArray.Num();
	}
	else 
	{ 
		CharacterMeshIdx = (CharacterMeshIdx + (CharacterMeshArray.Num() - 1)) % CharacterMeshArray.Num();
	}
	CharacterMeshArray[CharacterMeshIdx]->SetVisibility(true);
}

USkeletalMesh* ACharacterSelection::GetSelectedSkeletalMesh()
{
	return CharacterMeshArray[CharacterMeshIdx]->SkeletalMesh;
}

