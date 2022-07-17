// Copyright Epic Games, Inc. All Rights Reserved.

#include "VariableReplicationGameMode.h"
#include "VariableReplicationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVariableReplicationGameMode::AVariableReplicationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
