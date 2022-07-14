// Copyright Epic Games, Inc. All Rights Reserved.

#include "OwnershipRolesGameMode.h"
#include "OwnershipRolesCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOwnershipRolesGameMode::AOwnershipRolesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
