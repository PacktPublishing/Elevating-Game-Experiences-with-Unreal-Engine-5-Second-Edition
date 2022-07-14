#include "FPSCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AFPSCharacter::AFPSCharacter()
{
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(GetMesh(), "Camera");

	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCharacterMovement()->JumpZVelocity = 600.0f;

	PrimaryActorTick.bCanEverTick = false;
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(GetWorld(), SpawnSound);
	
	if (!HasAuthority())
	{
		return;
	}

	SetHealth(MaxHealth);
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	const APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (EnhancedPlayerInputComponent == nullptr || PlayerController == nullptr)
	{
		return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if(EnhancedSubsystem == nullptr)
	{
		return;
	}

	EnhancedSubsystem->AddMappingContext(InputMappingContext, 1);

	EnhancedPlayerInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);
	EnhancedPlayerInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Look);
	EnhancedPlayerInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ACharacter::Jump);
}

void AFPSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION(AFPSCharacter, Health, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AFPSCharacter, Armor, COND_OwnerOnly);
}

void AFPSCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D InputValue = Value.Get<FVector2D>();

	if(InputValue.X != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), InputValue.X);
	}

	if(InputValue.Y != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), InputValue.Y);	
	}
}

void AFPSCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D InputValue = Value.Get<FVector2D>();

	if(InputValue.X != 0.0f)
	{
		AddControllerYawInput(InputValue.X);
	}

	if(InputValue.Y != 0.0f)
	{
		AddControllerPitchInput(InputValue.Y);	
	}
}

void AFPSCharacter::ArmorAbsorbDamage(float & Damage)
{
	const float AbsorbedDamage = Damage * ArmorAbsorption;
	const float RemainingArmor = Armor - AbsorbedDamage;

	SetArmor(RemainingArmor);

	Damage = (Damage * (1 - ArmorAbsorption)) - FMath::Min(RemainingArmor, 0.0f);
}