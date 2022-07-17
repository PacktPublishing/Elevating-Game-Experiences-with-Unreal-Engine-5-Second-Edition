// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "FPSCharacter.h"

void AHealthPickup::OnPickedUp(AFPSCharacter* Character)
{
	Super::OnPickedUp(Character);

	Character->AddHealth(HealAmount);
}