// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

class UParticleSystem;
class UCameraShakeBase;


UCLASS()
class COOPGAME_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWeapon();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Componnets")
	USkeletalMeshComponent* SkeletaMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	TSubclassOf<UDamageType> DamageType;

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
	void PlayImpactEffect(FHitResult HitResult);


	// Camera shake
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<UCameraShakeBase> FireCameraShake;

	void PlayCameraShake();

public:	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	virtual void Fire();
};
