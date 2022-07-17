// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"
#include "FPSCharacter.h"

void AWeaponPickup::OnPickedUp(AFPSCharacter* Character)
{
	Super::OnPickedUp(Character);

	Character->AddWeapon(WeaponType);
	Character->AddAmmo(static_cast<EAmmoType>(WeaponType), AmmoAmount);
}