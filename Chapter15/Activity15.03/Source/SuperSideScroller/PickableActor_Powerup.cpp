// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Powerup.h"
#include "SuperSideScroller_Player.h"

void APickableActor_Powerup::BeginPlay()
{
	Super::BeginPlay();
}

void APickableActor_Powerup::PlayerPickedUp(ASuperSideScroller_Player* Player)
{
	Super::PlayerPickedUp(Player);
	Player->IncreaseMovementPowerup();
}
