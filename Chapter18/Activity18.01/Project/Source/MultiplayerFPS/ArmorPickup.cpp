// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorPickup.h"
#include "FPSCharacter.h"

void AArmorPickup::OnPickedUp(AFPSCharacter* Character)
{
	Super::OnPickedUp(Character);

	Character->AddArmor(ArmorAmount);
}