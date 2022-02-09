// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UCharacterMovementComponent;
class ASWeapon;

UCLASS()
class COOPGAME_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UCameraComponent* ThirdViewCameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USpringArmComponent* SprintArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* FirstViewCameraComp;

	void BeginCrouch();
	void EndCrouch();

	UCharacterMovementComponent* CharacterMovementComp;
	void BeginRun();
	void EndRun();
	float WalkSpeed;
	float RunSpeed;


	UCameraComponent* CurrentViewCameraComp;
	void SwitchViewFromTwoCamera();

	
	// CameraZoom AKA Aim
	bool bWantToZoom;
	UPROPERTY(EditDefaultsOnly, Category="Zoom")
	float ZoomedFov;
	float DefalutFov;
	UPROPERTY(EditDefaultsOnly, Category="Zoom")
	float ZoomInterpSpeed;

	void BeginZoom();
	void EndZoom();
	void FovZoom(float DeltaTime);


	// Weapon
	UPROPERTY(BlueprintReadWrite, Category="Weapon")
	ASWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<ASWeapon> StarterWeaponClass;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	FName WeaponAttachSocketName;

	void CreateWeapon();
	// use weapon Fire Function
	void Fire();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector GetPawnViewLocation() const override;
};
