// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Base.h"
#include "Components/SphereComponent.h" 
#include "Components/StaticMeshComponent.h" 
#include "GameFramework/RotatingMovementComponent.h"
#include "SuperSideScroller_Player.h"
#include "Kismet/GameplayStatics.h" 

// Sets default values
APickableActor_Base::APickableActor_Base()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(30.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp")); 
	MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RotationComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationComp"));

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APickableActor_Base::BeginOverlap);
}

void APickableActor_Base::PlayerPickedUp(ASuperSideScroller_Player* Player)
{
	if(class UWorld* World = GetWorld())
	{
		if(PickupSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(World, PickupSound, GetActorLocation());
		}
	}
	Destroy();
}

void APickableActor_Base::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(class ASuperSideScroller_Player* Player = Cast<ASuperSideScroller_Player>(OtherActor))
	{
		PlayerPickedUp(Player);
	}
}

// Called when the game starts or when spawned
void APickableActor_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

