// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameMode.h"
#include "Components/SHealthComponent.h"
#include "SGameState.h"
#include "SPlayerState.h"

ASGameMode::ASGameMode()
{
	NrOfBaseSpawn = 2;
	NrOfBotsToSpawn = 0;

	TimeBetweenSpawn = 1;
	TimeBetweenWaves = 5;

	WaveCount = 0;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;

	GameStateClass = ASGameState::StaticClass();
	PlayerStateClass = ASPlayerState::StaticClass();
}

void ASGameMode::StartWave()
{
	WaveCount++;
	NrOfBotsToSpawn = NrOfBaseSpawn * WaveCount;

	SetWaveState(EWaveState::WaveInProgress);
	GetWorldTimerManager().SetTimer(TimerHandle_BotSpawner, this, &ASGameMode::SpawnBotTimerElaped, TimeBetweenSpawn, true, 0.0f);
}

void ASGameMode::EndWave()
{
	SetWaveState(EWaveState::WaveComplete);
	GetWorldTimerManager().ClearTimer(TimerHandle_BotSpawner);
}

void ASGameMode::PrepareNextWave()
{
	SetWaveState(EWaveState::WatingToStart);
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
}

/* just Server can run this code, Because just Server has GameMode class */
void ASGameMode::SetWaveState(EWaveState NewState)
{
	ASGameState* GS = GetGameState<ASGameState>();
	if (ensureAlways(GS))
	{
		GS->WaveState = NewState;
		GS->OnRep_WaveState(NewState);
	}
}

void ASGameMode::RestartDeadPlayer()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator();It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn() == nullptr)
		{
			RestartPlayer(PC);
		}
	}
}

void ASGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckWaveState();
	RestartDeadPlayer();
}

