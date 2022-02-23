// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameMode.h"
#include "Components/SHealthComponent.h"

ASGameMode::ASGameMode()
{
	NrOfBaseSpawn = 2;
	NrOfBotsToSpawn = 0;

	TimeBetweenSpawn = 1;
	TimeBetweenWaves = 5;

	WaveCount = 0;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;
}

void ASGameMode::StartWave()
{
	WaveCount++;
	NrOfBotsToSpawn = NrOfBaseSpawn * WaveCount;

	GetWorldTimerManager().SetTimer(TimerHandle_BotSpawner, this, &ASGameMode::SpawnBotTimerElaped, TimeBetweenSpawn, true, 0.0f);
}

void ASGameMode::EndWave()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BotSpawner);
}

void ASGameMode::PrepareNextWave()
{
	GetWorldTimerManager().SetTimer(TimerHandle_PrepareSpawn, this, &ASGameMode::StartWave, TimeBetweenWaves);
}

void ASGameMode::SpawnBotTimerElaped()
{
	SpawnNewBot();
	NrOfBotsToSpawn--;

	if (NrOfBotsToSpawn <= 0)
	{
		EndWave();
	}
	
}

void ASGameMode::CheckWaveState()
{
	bool bIsPreparingNextWave = GetWorldTimerManager().IsTimerActive(TimerHandle_PrepareSpawn);
	if (bIsPreparingNextWave || NrOfBotsToSpawn > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("not prepare"));
		return;
	}

	bool bIsAnyBotAlive = false;
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		APawn* TestPawn = It->Get();
		if (TestPawn == nullptr || TestPawn->IsPlayerControlled())
		{
			continue;
		}
		USHealthComponent* HealthComp = Cast<USHealthComponent>(TestPawn->GetComponentByClass(USHealthComponent::StaticClass()));
		if (HealthComp && HealthComp->GetHealth() >= 0)
		{
			bIsAnyBotAlive = true;
			break;
		}
	}
	if (!bIsAnyBotAlive)
	{
		PrepareNextWave();
	}
	UE_LOG(LogTemp, Warning, TEXT("at least one bot alive!"));
}

void ASGameMode::StartPlay()
{
	Super::StartPlay();

}

void ASGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckWaveState();
}

