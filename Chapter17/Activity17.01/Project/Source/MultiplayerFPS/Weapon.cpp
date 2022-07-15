// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "FPSCharacter.h"

AWeapon::AWeapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	RootComponent = Mesh;

	bReplicates = true;
	
	PrimaryActorTick.bCanEverTick = false;
}

void AWeapon::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
	
	Character = Cast<AFPSCharacter>(NewOwner);
}

void AWeapon::StartFire()
{
	if (!bWantsFire || GetWorldTimerManager().GetTimerRemaining(FireTimer) > 0.0f)
	{
		return;
	}

	if (Character->GetAmmo(AmmoType) == 0)
	{
		if(NoAmmoSound != nullptr)
		{
			Character->ClientPlaySound2D(NoAmmoSound);
		}
		
		return;
	}
	
	Character->ConsumeAmmo(AmmoType, 1);

	const FVector FireLocation = Character->GetCameraLocation();
	const FVector FireDirection = Character->GetCameraDirection();
	
	FireHitscan(FireLocation, FireDirection);

	if (FireAnimMontage != nullptr)
	{
		Character->MulticastPlayAnimMontage(FireAnimMontage);
	}
	
	if (FireMode == EWeaponFireMode::Automatic && bWantsFire)
	{
		GetWorldTimerManager().SetTimer(FireTimer, this, &AWeapon::StartFire, FireRate);
	}
	else if (FireMode == EWeaponFireMode::Single)
	{
		GetWorldTimerManager().SetTimer(FireTimer, FireRate, false);
	}
}

void AWeapon::FireHitscan(FVector FireLocation, FVector FireDirection)
{
	FHitResult Hit(ForceInit);
	FCollisionQueryParams TraceParams("Fire Trace", false, Character);
	
	const FVector Start = FireLocation;
	const FVector End = Start + FireDirection * HitscanRange;
	
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	AFPSCharacter* HitCharacter = Cast<AFPSCharacter>(Hit.GetActor());
	
	if (HitCharacter != nullptr)
	{
		HitCharacter->ApplyDamage(HitscanDamage, Character);
	}
}

void AWeapon::ServerStartFire_Implementation()
{
	bWantsFire = true;

	StartFire();
}

void AWeapon::ServerStopFire_Implementation()
{
	bWantsFire = false;
}