// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupsPlayerState.h"
#include "Net/UnrealNetwork.h"

void APickupsPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APickupsPlayerState, Pickups);
}

