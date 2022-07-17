// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERFPS_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FPS Player Controller")
	TSubclassOf<class UPlayerMenu> PlayerMenuClass;

	UPROPERTY()
	UPlayerMenu* PlayerMenu;

	virtual void BeginPlay() override;

public:

	void ToggleScoreboard() const;

	UFUNCTION(Client, Reliable)
	void ClientNotifyKill(const FString& Name);

	UFUNCTION(Client, Reliable)
	void ClientShowScoreboard();
};
