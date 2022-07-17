// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnumerationsGameMode.h"
#include "EnumerationsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEnumerationsGameMode::AEnumerationsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
