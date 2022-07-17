#include "FPSCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Weapon.h"

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

	constexpr int32 WeaponCount = ENUM_TO_INT32(EWeaponType::MAX);
	
	Weapons.Init(nullptr, WeaponCount);

	constexpr int32 AmmoCount = ENUM_TO_INT32(EAmmoType::MAX);
	
	Ammo.Init(50, AmmoCount);

	for (int32 i = 0; i < WeaponCount; i++)
	{
		AddWeapon(static_cast<EWeaponType>(i));
	}

	EquipWeapon(EWeaponType::MachineGun, false);
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
	EnhancedPlayerInputComponent->BindAction(FireInputAction, ETriggerEvent::Started, this, &AFPSCharacter::StartFire);
	EnhancedPlayerInputComponent->BindAction(FireInputAction, ETriggerEvent::Completed, this, &AFPSCharacter::StopFire);
	EnhancedPlayerInputComponent->BindAction(PistolInputAction, ETriggerEvent::Started, this, &AFPSCharacter::Pistol);
	EnhancedPlayerInputComponent->BindAction(MachineGunInputAction, ETriggerEvent::Started, this, &AFPSCharacter::MachineGun);
	EnhancedPlayerInputComponent->BindAction(RailgunInputAction, ETriggerEvent::Started, this, &AFPSCharacter::Railgun);
	EnhancedPlayerInputComponent->BindAction(PreviousWeaponInputAction, ETriggerEvent::Started, this, &AFPSCharacter::PreviousWeapon);
	EnhancedPlayerInputComponent->BindAction(NextWeaponInputAction, ETriggerEvent::Started, this, &AFPSCharacter::NextWeapon);
}

void AFPSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION(AFPSCharacter, Health, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AFPSCharacter, Armor, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AFPSCharacter, Weapon, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AFPSCharacter, Weapons, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(AFPSCharacter, Ammo, COND_OwnerOnly);
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

void AFPSCharacter::StartFire(const FInputActionValue& Value)
{
	if (Weapon != nullptr)
	{
		Weapon->ServerStartFire();
	}
}
void AFPSCharacter::StopFire(const FInputActionValue& Value)
{
	if (Weapon != nullptr)
	{
		Weapon->ServerStopFire();
	}
}

void AFPSCharacter::Pistol(const FInputActionValue& Value)
{
	ServerEquipWeapon(EWeaponType::Pistol);
}
void AFPSCharacter::MachineGun(const FInputActionValue& Value)
{
	ServerEquipWeapon(EWeaponType::MachineGun);
}
void AFPSCharacter::Railgun(const FInputActionValue& Value)
{
	ServerEquipWeapon(EWeaponType::Railgun);
}

void AFPSCharacter::PreviousWeapon(const FInputActionValue& Value)
{
	ServerCycleWeapons(-1);
}
void AFPSCharacter::NextWeapon(const FInputActionValue& Value)
{
	ServerCycleWeapons(1);
}

void AFPSCharacter::ArmorAbsorbDamage(float & Damage)
{
	const float AbsorbedDamage = Damage * ArmorAbsorption;
	const float RemainingArmor = Armor - AbsorbedDamage;

	SetArmor(RemainingArmor);

	Damage = (Damage * (1 - ArmorAbsorption)) - FMath::Min(RemainingArmor, 0.0f);
}

void AFPSCharacter::ServerCycleWeapons_Implementation(int32 Direction)
{
	const int32 WeaponCount = Weapons.Num();
	const int32 StartWeaponIndex = GET_WRAPPED_ARRAY_INDEX(WeaponIndex + Direction, WeaponCount);
	
	for (int32 i = StartWeaponIndex; i != WeaponIndex; i = GET_WRAPPED_ARRAY_INDEX(i + Direction, WeaponCount))
	{
		if (EquipWeapon(static_cast<EWeaponType>(i)))
		{
			break;
		}
	}
}

void AFPSCharacter::ServerEquipWeapon_Implementation(EWeaponType WeaponType)
{
	EquipWeapon(WeaponType);
}

bool AFPSCharacter::EquipWeapon(EWeaponType WeaponType, bool bPlaySound)
{
	const int32 NewWeaponIndex = ENUM_TO_INT32(WeaponType);
	
	if (!Weapons.IsValidIndex(NewWeaponIndex))
	{
		return false;
	}
	
	AWeapon* NewWeapon = Weapons[NewWeaponIndex];
	
	if (NewWeapon == nullptr || Weapon == NewWeapon)
	{
		return false;
	}

	if (Weapon != nullptr)
	{
		Weapon->SetActorHiddenInGame(true);
	}
	
	Weapon = NewWeapon;
	Weapon->SetActorHiddenInGame(false);
	
	WeaponIndex = NewWeaponIndex;

	if (WeaponChangeSound != nullptr && bPlaySound)
	{
		ClientPlaySound2D(WeaponChangeSound);
	}

	return true;
}

void AFPSCharacter::AddWeapon(EWeaponType WeaponType)
{
	const int32 NewWeaponIndex = ENUM_TO_INT32(WeaponType);
	
	if (!WeaponClasses.IsValidIndex(NewWeaponIndex) || Weapons[NewWeaponIndex] != nullptr)
	{
		return;
	}
	
	UClass* WeaponClass = WeaponClasses[NewWeaponIndex];
	
	if (WeaponClass == nullptr)
	{
		return;
	}

	FActorSpawnParameters SpawnParameters = FActorSpawnParameters();
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AWeapon* NewWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, SpawnParameters);
	
	if (NewWeapon == nullptr)
	{
		return;
	}

	NewWeapon->SetActorHiddenInGame(true);
	Weapons[NewWeaponIndex] = NewWeapon;
	NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "GripPoint");
}

void AFPSCharacter::MulticastPlayAnimMontage_Implementation(UAnimMontage* AnimMontage)
{
	PlayAnimMontage(AnimMontage);
}
void AFPSCharacter::ClientPlaySound2D_Implementation(USoundBase* Sound)
{
	UGameplayStatics::PlaySound2D(GetWorld(), Sound);
}

void AFPSCharacter::ApplyDamage(float Damage, AFPSCharacter* DamageCauser)
{
	if (IsDead())
	{
		return;
	}

	ArmorAbsorbDamage(Damage);
	RemoveHealth(Damage);

	if (HitSound != nullptr && DamageCauser != nullptr)
	{
		DamageCauser->ClientPlaySound2D(HitSound);
	}
}

int32 AFPSCharacter::GetWeaponAmmo() const
{
	return Weapon != nullptr ? Ammo[ENUM_TO_INT32(Weapon->GetAmmoType())] : 0;
}

FVector AFPSCharacter::GetCameraLocation() const
{
	return Camera->GetComponentLocation();
}

FVector AFPSCharacter::GetCameraDirection() const
{
	return GetControlRotation().Vector();
}