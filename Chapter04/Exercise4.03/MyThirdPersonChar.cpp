// Fill out your copyright notice in the Description page of Project Settings.

#include "MyThirdPersonChar.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Controller.h"

// Sets default values
AMyThirdPersonChar::AMyThirdPersonChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AMyThirdPersonChar::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyThirdPersonChar::Move(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();
	if (Controller != nullptr && (InputValue.X != 0.0f || InputValue.Y != 0.0f))
	{
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

		if (InputValue.X != 0.0f)
		{
			// get right vector 
			const FVector RightDirection = UKismetMathLibrary::GetRightVector(YawRotation);
			// add movement in that direction
			AddMovementInput(RightDirection, InputValue.X);
		}

		if (InputValue.Y != 0.0f)
		{
			// get forward vector
			const FVector ForwardDirection = YawRotation.Vector();
			AddMovementInput(ForwardDirection, InputValue.Y);
		}
	}
}

void AMyThirdPersonChar::Look(const FInputActionValue& Value)
{
	FVector2D InputValue = Value.Get<FVector2D>();

	if (InputValue.X != 0.0f)
	{
		AddControllerYawInput(InputValue.X);
	}
	if (InputValue.Y != 0.0f)
	{
		AddControllerPitchInput(InputValue.Y);
	}
}

void AMyThirdPersonChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyThirdPersonChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedPlayerInputComponent != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController != nullptr)
		{
			UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
			if (EnhancedSubsystem != nullptr)
			{
				EnhancedSubsystem->AddMappingContext(IC_Character, 1);
			}
		}

		EnhancedPlayerInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMyThirdPersonChar::Move);
		EnhancedPlayerInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedPlayerInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedPlayerInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyThirdPersonChar::Look);
	}
}

