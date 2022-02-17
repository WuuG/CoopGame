// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, USHealthComponent*, OwingHealthComp, float, Health, float, HealthDelta, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);

USTRUCT()
struct FDamageInfo
{
	GENERATED_BODY()

public:
	float Damage;
	const class UDamageType* DamageType;
	class AController* InstigatedBy;
	AActor* DamageCauser;
};

UCLASS( ClassGroup=(COOP), meta=(BlueprintSpawnableComponent) )
class COOPGAME_API USHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(Replicated,BlueprintReadOnly, Category="Player", ReplicatedUsing=OnRep_HealthChange)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player")
	float DefalutHealth;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnRep_HealthChange();

	FDamageInfo DamageInfo;

public:	

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnHealthChangedSignature OnHealthChanged;

	float GetHealth();
};
