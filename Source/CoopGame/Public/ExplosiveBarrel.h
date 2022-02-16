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

	// Mesh and Meterial
	UPROPERTY(VisibleAnywhere,  Category="Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category="Metetials")
	UMaterial* M_Explosive;

	UPROPERTY(EditDefaultsOnly, Category="Metetials")
	UMaterial* M_Exploded;


	//FX
	UPROPERTY(EditDefaultsOnly, Category="FX")
	UParticleSystem* ExplodeEffect;

	USHealthComponent* HealthComp;

	UPROPERTY(ReplicatedUsing=OnRep_Exploded, VisibleInstanceOnly,Category="Explode")
	bool bExpoled;
	float ExplodeRadius;
	
	UPROPERTY(EditDefaultsOnly, Category = "Explode")
	float ExplodeStrength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Explode")
	TSubclassOf<UDamageType> ExplodeDamageType;

	UFUNCTION()
	void OnBarrelHealthChanged(USHealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void PlayExplodeEffect();

	void Explode();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Explode();

	UFUNCTION()
	void OnRep_Exploded();

};
