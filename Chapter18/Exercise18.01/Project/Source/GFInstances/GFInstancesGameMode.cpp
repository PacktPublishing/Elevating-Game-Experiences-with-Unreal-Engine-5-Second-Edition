// Copyright Epic Games, Inc. All Rights Reserved.

#include "GFInstancesGameMode.h"
#include "GFInstancesCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGFInstancesGameMode::AGFInstancesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
