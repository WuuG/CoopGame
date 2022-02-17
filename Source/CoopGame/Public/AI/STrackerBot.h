// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "STrackerBot.generated.h"

class UStaticMeshComponent;
class USHealthComponent;
class USphereComponent;
class UParticleSystem;

UCLASS()
class COOPGAME_API ASTrackerBot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASTrackerBot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Component")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category="Component")
	USHealthComponent* HealtComp;

	UPROPERTY(VisibleAnywhere, Category="Component")
	USphereComponent* SphereComp;

	// Nav
	FVector NextPathPoint;
	UPROPERTY(EditDefaultsOnly, Category="Navagation")
	float DistanceOfFindPath;
	UPROPERTY(EditDefaultsOnly, Category="Navagation")
	float MoveForce;
	UPROPERTY(EditDefaultsOnly, Category="Navagation")
	bool bUseVelocityChange;

	FVector GetNextPathPoint();

	// Material
	UMaterialInstanceDynamic* MatInst;

	// Explosion
	UPROPERTY(EditDefaultsOnly, Category="Explosion")
	UParticleSystem* ExplosionEffect;
	UPROPERTY(EditDefaultsOnly, Category="Explosion")
	float ExplosionDamage;
	UPROPERTY(EditDefaultsOnly, Category="Explosion")
	float ExplosionRadius;
	UPROPERTY(EditDefaultsOnly, Category="Explosion")
	bool ExplosionFullDamage;
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	float SelfDestructDamage;
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	float DamageSelfInterval;
	bool bExploded;

	UPROPERTY(EditDefaultsOnly, Category="Explosion")
	float SphereRaius;
	bool bStartSelfDestructed;
	FTimerHandle TimerHandler_StartSelfConstruct;

	UFUNCTION()
	void HandleTakeDamage(USHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void SelfDestruct();
	void PlayExplosionEffect();

	void DamageSelf();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
