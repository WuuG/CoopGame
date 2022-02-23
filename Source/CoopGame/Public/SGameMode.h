// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameMode.generated.h"

/**
 * 
 */
UCLASS()
class COOPGAME_API ASGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	ASGameMode();

	FTimerHandle TimerHandle_BotSpawner;
	FTimerHandle TimerHandle_PrepareSpawn;

	int32 NrOfBotsToSpawn;

	int32 WaveCount;

	UPROPERTY(EditDefaultsOnly, Category="SpawnBots")
	float TimeBetweenWaves;

	UPROPERTY(EditDefaultsOnly, Category="SpawnBots")
	float TimeBetweenSpawn;

	UPROPERTY(EditDefaultsOnly, Category="SpawnBots")
	int32 NrOfBaseSpawn;

	UFUNCTION(BlueprintImplementableEvent, Category="SpawnBotsEvent")
	void SpawnNewBot();

	void StartWave();

	void EndWave();

	void PrepareNextWave();

	void SpawnBotTimerElaped();

	void CheckWaveState();

public:
	virtual void StartPlay() override;
	
	virtual void Tick(float DeltaTime) override;
};
