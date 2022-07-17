// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "ArmorPickup.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERFPS_API AArmorPickup : public APickup
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armor Pickup")
	float ArmorAmount = 20.0f;

	virtual void OnPickedUp(AFPSCharacter* Character) override;
};
