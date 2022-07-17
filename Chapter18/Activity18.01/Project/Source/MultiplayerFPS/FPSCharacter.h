// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "EnumTypes.h"
#include "MultiplayerFPS.h"
#include "FPSCharacter.generated.h"

UCLASS()
class MULTIPLAYERFPS_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FPS Character")
	class UCameraComponent* Camera;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "FPS Character")
	float Health = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Character")
	float MaxHealth = 100.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "FPS Character")
	float Armor = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Character")
	float MaxArmor = 100.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Character")
	float ArmorAbsorption = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* MoveInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* JumpInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* FireInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* PistolInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* MachineGunInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* RailgunInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* PreviousWeaponInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* NextWeaponInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ScoreboardInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Character")
	USoundBase* SpawnSound = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Character")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Character")
	USoundBase* PainSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Character")
	USoundBase* LandSound;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Character")
	USoundBase* WeaponChangeSound;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "FPS Character")
	TArray<int32> Ammo;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "FPS Character")
	TArray<class AWeapon*> Weapons;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Character")
	TArray<TSubclassOf<AWeapon>> WeaponClasses;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "FPS Character")
	AWeapon* Weapon;

	UPROPERTY()
	class AMultiplayerFPSGameModeBase* GameMode;
	
	int32 WeaponIndex = INDEX_NONE;

	AFPSCharacter();
	
	virtual void BeginPlay() override;	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;	
	virtual void FellOutOfWorld(const UDamageType& DmgType) override;	
	virtual void Landed(const FHitResult& Hit) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartFire(const FInputActionValue& Value);
	void StopFire(const FInputActionValue& Value);
	void Pistol(const FInputActionValue& Value);
	void MachineGun(const FInputActionValue& Value);
	void Railgun(const FInputActionValue& Value);
	void PreviousWeapon(const FInputActionValue& Value);
	void NextWeapon(const FInputActionValue& Value);
	void Scoreboard(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void ServerCycleWeapons(int32 Direction);

	UFUNCTION(Server, Reliable)
	void ServerEquipWeapon(EWeaponType WeaponType);

	bool EquipWeapon(EWeaponType WeaponType, bool bPlaySound = true);

public:
	
	void ApplyDamage(float Damage, AFPSCharacter* DamageCauser);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastPlayAnimMontage(UAnimMontage* AnimMontage);

	UFUNCTION(Client, Unreliable)
	void ClientPlaySound2D(USoundBase* Sound);

	void AddWeapon(EWeaponType WeaponType);

	UFUNCTION(BlueprintCallable, Category = "FPS Character")
	int32 GetWeaponAmmo() const;

	void AddAmmo(EAmmoType AmmoType, int32 Amount) { SetAmmo(AmmoType, GetAmmo(AmmoType) + Amount); }
	void ConsumeAmmo(EAmmoType AmmoType, int32 Amount) { SetAmmo(AmmoType, GetAmmo(AmmoType) - Amount); }
	int32 GetAmmo(EAmmoType AmmoType) const { return Ammo[ENUM_TO_INT32(AmmoType)]; }
	void SetAmmo(EAmmoType AmmoType, int32 Amount) { Ammo[ENUM_TO_INT32(AmmoType)] = FMath::Max(0, Amount); }

	FVector GetCameraLocation() const;
	FVector GetCameraDirection() const;

	void AddHealth(float Amount) { SetHealth(Health + Amount); }
	void RemoveHealth(float Amount) { SetHealth(Health - Amount); }
	void SetHealth(float NewHealth) { Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth); }
	bool IsDead() const { return Health == 0.0f; }

	void AddArmor(float Amount) { SetArmor(Armor + Amount); }
	void SetArmor(float Amount) { Armor = FMath::Clamp(Amount, 0.0f, MaxArmor); }
	void ArmorAbsorbDamage(float & Damage);
};
