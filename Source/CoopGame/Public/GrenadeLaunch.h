// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWeapon.h"
#include "GrenadeLaunch.generated.h"

/**
 * 
 */
UCLASS()
class COOPGAME_API AGrenadeLaunch : public ASWeapon
{
	GENERATED_BODY()

	void Fire() override;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<AActor> ProjectileClass;
};
