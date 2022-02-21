// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpActor.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
	PowerUpInterval = 10.0f;
	TotalNrOfTicks = 1;
	TickProcessed = 0;

	bIsPowerUpActive = false;

	SetReplicates(true);
}

void ASPowerUpActor::OnTickPowerUp()
{
	TickProcessed++;
	OnPowerUpTicked();
	if (TickProcessed >= TotalNrOfTicks)
	{
		bIsPowerUpActive = false;
		OnExpired();
		GetWorldTimerManager().ClearTimer(TimerHandle_PowerUpTick);
	}
}

void ASPowerUpActor::OnRep_PowerUpActive()
{
	// Server And Client
	if (bIsPowerUpActive)
	{
		OnHideMesh();
	}
	if (GetLocalRole() == ROLE_Authority)
	{
		return;
	}
	// Just Client
	if (bIsPowerUpActive)
	{
		OnClientActivated();
	}
	else
	{
		OnClientExpired();
	}
}

// Called when the game starts or when spawned
void ASPowerUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

/*
*	Just Server can run this code
*/
void ASPowerUpActor::ActivatePowerup(AActor* OtherActor)
{
	OnActivated(OtherActor);
	bIsPowerUpActive = true;
	OnRep_PowerUpActive();

	if (PowerUpInterval > 0)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerUpTick, this, &ASPowerUpActor::OnTickPowerUp, PowerUpInterval,true);
	}
	else 
	{
		OnTickPowerUp();
	}
}

void ASPowerUpActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASPowerUpActor, bIsPowerUpActive);
}

