// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerProjectile::APlayerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp")); 

	CollisionComp->InitSphereRadius(15.0f); 
	CollisionComp->BodyInstance.SetCollisionProfileName("BlockAll"); 
	CollisionComp->OnComponentHit.AddDynamic(this, &APlayerProjectile::OnHit);
	
	// Set as root component 
	RootComponent = CollisionComp; 

	// Use a ProjectileMovementComponent to govern this projectile's movement 
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp")); 

	ProjectileMovement->UpdatedComponent = CollisionComp; 
	ProjectileMovement->ProjectileGravityScale = 0.0f; 
	ProjectileMovement->InitialSpeed = 800.0f; 
	ProjectileMovement->MaxSpeed = 800.0f;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	if(MeshComp)
	{
		MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	}
	
	InitialLifeSpan = 3.0f; 
}

void APlayerProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
}

