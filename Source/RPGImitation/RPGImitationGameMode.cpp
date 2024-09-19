// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGImitationGameMode.h"
#include "RPGImitationCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARPGImitationGameMode::ARPGImitationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
