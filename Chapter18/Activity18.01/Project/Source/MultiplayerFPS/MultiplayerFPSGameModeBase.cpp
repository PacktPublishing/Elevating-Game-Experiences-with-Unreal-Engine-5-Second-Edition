// Copyright Epic Games, Inc. All Rights Reserved.


#include "MultiplayerFPSGameModeBase.h"
#include "FPSPlayerState.h"
#include "FPSGameState.h"
#include "FPSCharacter.h"
#include "FPSPlayerController.h"
#include "Kismet/GameplayStatics.h"

AMultiplayerFPSGameModeBase::AMultiplayerFPSGameModeBase()
{
	DefaultPawnClass = AFPSCharacter::StaticClass();
	PlayerControllerClass = AFPSPlayerController::StaticClass();
	PlayerStateClass = AFPSPlayerState::StaticClass();
	GameStateClass = AFPSGameState::StaticClass();
}

bool AMultiplayerFPSGameModeBase::ShouldSpawnAtStartSpot(AController* Player)
{
	return false;
}

void AMultiplayerFPSGameModeBase::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	AFPSGameState* FPSGameState = Cast<AFPSGameState>(GameState);

	if (FPSGameState != nullptr)
	{
		FPSGameState->SetKillLimit(KillLimit);
	}
}

void AMultiplayerFPSGameModeBase::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();

	TArray<AActor*> PlayerControllers;

	UGameplayStatics::GetAllActorsOfClass(this, AFPSPlayerController::StaticClass(), PlayerControllers);

	for (AActor* PlayerController : PlayerControllers)
	{
		AFPSPlayerController* FPSPlayerController = Cast<AFPSPlayerController>(PlayerController);

		if (FPSPlayerController == nullptr)
		{
			continue;
		}

		APawn* Pawn = FPSPlayerController->GetPawn();

		if (Pawn != nullptr)
		{
			Pawn->Destroy();
		}

		FPSPlayerController->ClientShowScoreboard();
	}

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMultiplayerFPSGameModeBase::RestartMap, 5.0f);
}

bool AMultiplayerFPSGameModeBase::ReadyToEndMatch_Implementation()
{
	return HasWinner();
}

bool AMultiplayerFPSGameModeBase::HasWinner() const
{
	for (APlayerState* PlayerState : GameState->PlayerArray)
	{
		const AFPSPlayerState* FPSPlayerState = Cast<AFPSPlayerState>(PlayerState);

		if (FPSPlayerState != nullptr && FPSPlayerState->GetKills() == KillLimit)
		{
			return true;
		}
	}

	return false;
}

void AMultiplayerFPSGameModeBase::OnKill(AController* KillerController, AController* VictimController)
{
	if (!IsMatchInProgress())
	{
		return;
	}

	if (KillerController != nullptr && KillerController != VictimController)
	{
		AFPSPlayerState* KillerPlayerState = Cast<AFPSPlayerState>(KillerController->PlayerState);

		if (KillerPlayerState != nullptr)
		{
			KillerPlayerState->AddKill();
		}

		AFPSPlayerController* KillerFPSController = Cast<AFPSPlayerController>(KillerController);

		if (KillerFPSController != nullptr && VictimController != nullptr && VictimController->PlayerState != nullptr)
		{
			KillerFPSController->
			ClientNotifyKill(VictimController->PlayerState->GetPlayerName());
		}
	}

	if (VictimController != nullptr)
	{
		AFPSPlayerState* VictimPlayerState = Cast<AFPSPlayerState>(VictimController->PlayerState);

		if (VictimPlayerState != nullptr)
		{
			VictimPlayerState->AddDeath();
		}

		APawn* Pawn = VictimController->GetPawn();

		if (Pawn != nullptr)
		{
			Pawn->Destroy();
		}

		if (!HasWinner())
		{
			RestartPlayer(VictimController);
		}
	}
}

void AMultiplayerFPSGameModeBase::RestartMap() const
{
	GetWorld()->ServerTravel(GetWorld()->GetName(), false, false);
}
