// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyThirdPersonChar.generated.h"

UCLASS()
class MYTHIRDPERSON_API AMyThirdPersonChar : public ACharacter
{
	GENERATED_BODY()

	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MyTPS_Cam, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// Follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MyTPS_Cam, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:
	// Sets default values for this character's properties
	AMyThirdPersonChar();

	UPROPERTY(EditAnywhere, Category = Input)
		class UInputMappingContext* IC_Character;

	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* IA_Jump;

	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* IA_Look;

	UPROPERTY(EditAnywhere, Category = Input)
		class UInputAction* IA_Walk;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void BeginWalking();

	void StopWalking();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
