// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCapsuleComponent;
class UCameraComponent;
class USpringArmComponent;
class UCharacterMovementComponent;
class ASWeapon;
enum EFireMode;
class USHealthComponent;

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

	UCapsuleComponent* CapsuleComp;

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

	// Run
	UCharacterMovementComponent* CharacterMovementComp;
	void BeginRun();
	void EndRun();

	UPROPERTY(EditDefaultsOnly, Category="Run")
	float RunMagnification;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_BeginRun();
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_EndRun();


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
	UPROPERTY(ReplicatedUsing=OnRep_WeaponChange ,VisibleAnywhere,BlueprintReadWrite, Category="Weapon")
	ASWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<ASWeapon> StarterWeaponClass;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	FName WeaponAttachSocketName;

	void CreateWeapon();

	UFUNCTION()
	void OnRep_WeaponChange();

	// use weapon Fire Function
	void StartFire();
	void StopFire();
	void SwitchFireMode();

	// Health
	UPROPERTY(Replicated,BlueprintReadOnly, Category="Player")
	bool bDied;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Player")
	USHealthComponent* HealthComp;

	UFUNCTION()
	void OnHealthChanged(USHealthComponent* OwingHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector GetPawnViewLocation() const override;
};
