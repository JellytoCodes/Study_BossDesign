// Copyright Epic Games, Inc. All Rights Reserved.

#include "BossDesignGameMode.h"
#include "BossDesignCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABossDesignGameMode::ABossDesignGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
