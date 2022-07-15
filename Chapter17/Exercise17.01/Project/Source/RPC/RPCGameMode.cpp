// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPCGameMode.h"
#include "RPCCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARPCGameMode::ARPCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
