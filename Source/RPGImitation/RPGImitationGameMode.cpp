// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGImitationGameMode.h"
#include "RPGImitationCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARPGImitationGameMode::ARPGImitationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/Contents/Blueprints/Characters/PlayerCharacter/BP_MyRPGCharacter.BP_MyRPGCharacter_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
