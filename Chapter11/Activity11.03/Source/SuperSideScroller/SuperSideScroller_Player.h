// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScrollerCharacter.h"
#include "SuperSideScroller_Player.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API ASuperSideScroller_Player : public ASuperSideScrollerCharacter
{
	GENERATED_BODY()
	
	//Constructor
	ASuperSideScroller_Player();

protected:
	//Override base character class function to set up our player input component
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* IC_Character;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Sprint;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Throw;

	//Sprinting
	void Sprint();

	//Stop Sprinting
	void StopSprinting();

	//Throw projectile
	void ThrowProjectile();

private:
	//Bool to control if we are sprinting. Failsafe.
	bool bIsSprinting;
	
};
