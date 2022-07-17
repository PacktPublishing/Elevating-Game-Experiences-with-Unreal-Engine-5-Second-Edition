// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "FPSCharacter.h"
#include "GameFramework/RotatingMovementComponent.h"

APickup::APickup()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetCollisionProfileName("OverlapAll");
	RootComponent = Mesh;

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>("Rotating Movement");
	RotatingMovement->RotationRate = FRotator(0.0, 90.0f, 0);

	bReplicates = true;

	PrimaryActorTick.bCanEverTick = false;
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnBeginOverlap);
}

void APickup::OnPickedUp(AFPSCharacter* Character)
{
	if (PickupSound != nullptr)
	{
		Character->ClientPlaySound2D(PickupSound);
	}
}

void APickup::SetIsEnabled(bool NewbIsEnabled)
{
	bIsEnabled = NewbIsEnabled;

	SetActorHiddenInGame(!bIsEnabled);
	SetActorEnableCollision(bIsEnabled);
}

void APickup::Respawn()
{
	SetIsEnabled(true);
}

void APickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);

	if (Character == nullptr || Character->IsDead() || !HasAuthority())
	{
		return;
	}

	OnPickedUp(Character);

	SetIsEnabled(false);

	GetWorldTimerManager().SetTimer(RespawnTimer, this, &APickup::Respawn, RespawnTime);
}