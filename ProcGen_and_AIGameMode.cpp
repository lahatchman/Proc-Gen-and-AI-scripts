// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProcGen_and_AIGameMode.h"
#include "ProcGen_and_AICharacter.h"
#include "UObject/ConstructorHelpers.h"

AProcGen_and_AIGameMode::AProcGen_and_AIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
