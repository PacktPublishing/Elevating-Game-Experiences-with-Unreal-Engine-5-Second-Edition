// Fill out your copyright notice in the Description page of Project Settings.


#include "GFInstancePlayerController.h"
#include "Blueprint/UserWidget.h"

void AGFInstancePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() && MenuClass != nullptr)
	{
		Menu = CreateWidget<UUserWidget>(this, MenuClass);
		
		if (Menu != nullptr)
		{
			Menu->AddToViewport(0);
		}
	}
}