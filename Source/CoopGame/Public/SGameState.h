// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SGameState.generated.h"

UENUM()
enum class EWaveState : uint8
{
	WatingToStart,

	WaveInProgress,

	WatingToComplete,

	WaveComplete,

	GameOver,
};


/**
 * 
 */
UCLASS()
class COOPGAME_API ASGameState : public AGameStateBase
{
	GENERATED_BODY()
protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "WaveState")
	void WaveStateChange(EWaveState NewWaveState, EWaveState OldWaveState);
public:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_WaveState, Category="WaveState")
	EWaveState WaveState;

	UFUNCTION()
	void OnRep_WaveState(EWaveState OldState);
};
