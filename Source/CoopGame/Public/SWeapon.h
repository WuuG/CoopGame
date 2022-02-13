// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

class UParticleSystem;
class UCameraShakeBase;

UENUM(BlueprintType)
namespace EMyEnum
{
	enum EFireMode 
	{
		SemiAuto,
		FullyAuto,
	};
}

UCLASS()
class COOPGAME_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWeapon();

protected:

	virtual void BeginPlay() override;

	// Mesh
	UPROPERTY(EditDefaultsOnly, Category="Componnets")
	USkeletalMeshComponent* SkeletaMeshComp;

	// Effect
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	UParticleSystem* DefalutImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	UParticleSystem* FleshImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	UParticleSystem* TraceEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	FName TraceTargetName;

	void PlayMuzzleEffect(FVector TraceEndLocation);
	void PlayImpactEffect(FHitResult HitResult, EPhysicalSurface SurfaceType);


	// Camera shake
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<UCameraShakeBase> FireCameraShake;

	void PlayCameraShake();

	// Fire
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	float RateOfFire = 500.0f;

	EMyEnum::EFireMode FireMode;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	bool bIsMulFireMode;
	const float BaseDamage = 20.0f; 
	float TimeBetweenShots;
	float LastFireTime;
	FTimerHandle TimerHandler_TimeBetweenShots;

	virtual void Fire();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void OnFireModeChange(EMyEnum::EFireMode NewFireMode);



public:	
	void StartFire();
	void StopFire();
	void SwitchMode();

	// Created
	UFUNCTION(BlueprintImplementableEvent, Category = "WeaponEvent")
	void OnWeaponCreated();
};
