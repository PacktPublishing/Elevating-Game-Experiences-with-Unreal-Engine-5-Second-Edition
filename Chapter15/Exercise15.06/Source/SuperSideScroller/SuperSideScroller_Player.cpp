// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Player.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "PlayerProjectile.h" 
#include "Engine/World.h" 
#include "Components/SphereComponent.h"
#include "TimerManager.h"

ASuperSideScroller_Player::ASuperSideScroller_Player()
{
	//Set sprinting to false by default.
	bIsSprinting = false;
	//Set our Max Walk Speed to 300.0f
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ASuperSideScroller_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedPlayerInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(EnhancedPlayerInput)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem> (PlayerController->GetLocalPlayer());
		if(EnhancedSubsystem)
		{
			EnhancedSubsystem->AddMappingContext(IC_Character, 1);
		}
		
		//Bind pressed action Sprint to your Sprint function
		EnhancedPlayerInput->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &ASuperSideScroller_Player::Sprint);

		//Bind released action Sprint to your StopSprinting function
		EnhancedPlayerInput->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ASuperSideScroller_Player::StopSprinting);

		//Bind the pressed action Throw to your ThrowProjectile function
		EnhancedPlayerInput->BindAction(IA_Throw, ETriggerEvent::Triggered, this, &ASuperSideScroller_Player::ThrowProjectile);
	}
}

void ASuperSideScroller_Player::Sprint()
{
	if(!bIsSprinting)
	{
		bIsSprinting = true;
		if(bHasPowerupActive)
		{
			GetCharacterMovement()->MaxWalkSpeed = 900.0f;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		}
	}
}

void ASuperSideScroller_Player::StopSprinting()
{
	if(bIsSprinting)
	{
		bIsSprinting = false;
		if(bHasPowerupActive)
		{
			GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		}
	}
}

void ASuperSideScroller_Player::ThrowProjectile()
{
	if(ThrowMontage)
	{
		const bool bIsMontagePlaying = GetMesh()->GetAnimInstance()->Montage_IsPlaying(ThrowMontage);
		if(!bIsMontagePlaying)
		{
			GetMesh()->GetAnimInstance()->Montage_Play(ThrowMontage, 1.0f);
		}
	}
}

void ASuperSideScroller_Player::EndPowerup()
{
	bHasPowerupActive = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f; 
	GetCharacterMovement()->JumpZVelocity = 1000.0f;

	UWorld* World = GetWorld(); 
	if (World) 
	{
		World->GetTimerManager().ClearTimer(PowerupHandle); 
	} 
}

void ASuperSideScroller_Player::IncreaseMovementPowerup()
{
	bHasPowerupActive = true;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f; 
	GetCharacterMovement()->JumpZVelocity = 1500.0f;

	UWorld* World = GetWorld(); 
	if (World) 
	{
		World->GetTimerManager().SetTimer(PowerupHandle, this, &ASuperSideScroller_Player::EndPowerup, 8.0f, false); 
	} 
}

void ASuperSideScroller_Player::SpawnProjectile()
{
	if(PlayerProjectile)
	{
		UWorld* World = GetWorld();
		if(World)
		{
			FActorSpawnParameters SpawnParams; 
			SpawnParams.Owner = this;
			const FVector SpawnLocation = this->GetMesh()->GetSocketLocation(FName("ProjectileSocket")); 
			const FRotator Rotation = GetActorForwardVector().Rotation();
			APlayerProjectile* Projectile = World->SpawnActor<APlayerProjectile>(PlayerProjectile, SpawnLocation, Rotation, SpawnParams);
		}
	}
}

void ASuperSideScroller_Player::IncrementNumberofCollectables(int32 Value)
{
	if(Value == 0) 

	{ 
		return;
	}
	else 
	{
		NumberofCollectables += Value;
		UE_LOG(LogTemp, Warning, TEXT("Number of Coins: %d"), NumberofCollectables);
	}
}
