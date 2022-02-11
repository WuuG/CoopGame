// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class UParticleSystem;
class UDamageType;

UCLASS()
class COOPGAME_API AExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,  Category="Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category="Metetials")
	UMaterial* M_Explosive;

	UPROPERTY(EditDefaultsOnly, Category="Metetials")
	UMaterial* M_Exploded;

	USHealthComponent* HealthComp;

	UPROPERTY(EditDefaultsOnly, Category="FX")
	UParticleSystem* ExplodeEffect;

	bool bExpoled;
	float ExplodeRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	TSubclassOf<UDamageType> ExplodeDamageType;

	UFUNCTION()
	void OnBarrelHealthChanged(USHealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void Explode();




};
