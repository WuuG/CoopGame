// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpActor.h"

class AActor;

// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
	PowerUpInterval = 10.0f;
	TotalNrOfTicks = 1;
	TickProcessed = 0;
}

void ASPowerUpActor::OnTickPowerUp()
{
	TickProcessed++;
	OnPowerUpTicked();
	if (TickProcessed >= TotalNrOfTicks)
	{
		OnExpired();
		GetWorldTimerManager().ClearTimer(TimerHandle_PowerUpTick);
	}
}

// Called when the game starts or when spawned
void ASPowerUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASPowerUpActor::ActivatePowerup(AActor* OtherActor)
{
	OnActivated(OtherActor);

	if (PowerUpInterval > 0)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerUpTick, this, &ASPowerUpActor::OnTickPowerUp, PowerUpInterval,true);
	}
	else 
	{
		OnTickPowerUp();
	}
}

