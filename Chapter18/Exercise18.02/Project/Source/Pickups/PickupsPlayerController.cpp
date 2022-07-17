// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupsPlayerController.h"
#include "Blueprint/UserWidget.h"

void APickupsPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalController() && ScoreboardMenuClass != nullptr)
	{
		ScoreboardMenu = CreateWidget<UUserWidget>(this, ScoreboardMenuClass);
	
		if (ScoreboardMenu != nullptr)
		{
			ScoreboardMenu->AddToViewport(0);
		}
	}
}

