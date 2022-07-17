// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerController.h"
#include "FPSCharacter.h"
#include "PlayerMenu.h"
#include "Blueprint/UserWidget.h"

void AFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() && PlayerMenuClass != nullptr)
	{
		PlayerMenu = CreateWidget<UPlayerMenu>(this, PlayerMenuClass);

		if (PlayerMenu != nullptr)
		{
			PlayerMenu->AddToViewport(0);
		}
	}
}

void AFPSPlayerController::ToggleScoreboard() const
{
	if (PlayerMenu != nullptr)
	{
		PlayerMenu->ToggleScoreboard();
	}
}

void AFPSPlayerController::ClientNotifyKill_Implementation(const FString& Name)
{
	if (PlayerMenu != nullptr)
	{
		PlayerMenu->NotifyKill(Name);
	}
}

void AFPSPlayerController::ClientShowScoreboard_Implementation()
{
	if (PlayerMenu != nullptr)
	{
		PlayerMenu->SetScoreboardVisibility(true);
	}
}
