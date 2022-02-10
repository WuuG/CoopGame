// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeLaunch.h"

void AGrenadeLaunch::Fire()
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{
		return;
	}
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector MuzzleLocation = SkeletaMeshComp->GetSocketLocation(MuzzleSocketName);
	
	PlayMuzzleEffect(FVector::ZeroVector);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, EyeRotation, SpawnParams);
	
	LastFireTime = GetWorld()->TimeSeconds;
}
