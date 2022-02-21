// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPowerUpActor.generated.h"

UCLASS()
class COOPGAME_API ASPowerUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPowerUpActor();

	/* powerUp props Tick interval time */
	UPROPERTY(EditDefaultsOnly, Category="PowerUps")
	float PowerUpInterval;

	/* Total number of ticks */
	UPROPERTY(EditDefaultsOnly, Category="PowerUps")
	int32 TotalNrOfTicks;

	int32 TickProcessed;

	FTimerHandle TimerHandle_PowerUpTick;

	UFUNCTION()
	void OnTickPowerUp();

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable, Category="PowerUps")
	void OnHideMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void ActivatePowerup(AActor* OtherActor);

	/* event for Execute power up effect */
	UFUNCTION(BlueprintImplementableEvent, Category="PowerUps")
	void OnActivated(AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent, Category="PowerUps")
	void OnPowerUpTicked();

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUps")
	void OnExpired();
};
