// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShake.h"
#include "CoopGame/CoopGame.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

static int32 DebugWeaponDrawing = 1;
FAutoConsoleVariableRef CVARDebugWeaponDrawing(TEXT("COOP.DebugWeapons"), DebugWeaponDrawing, TEXT("Draw Debug Lines for Weapon"), ECVF_Cheat);

// Sets default values
ASWeapon::ASWeapon()
{
	SkeletaMeshComp = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	SkeletaMeshComp->SetupAttachment(RootComponent);

	MuzzleSocketName = "MuzzleSocket";
	TraceTargetName = "BeamEnd";
}

void ASWeapon::Fire()
{
	PlayCameraShake();

	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector EndLocation = EyeLocation + EyeRotation.Vector() * 10000;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(MyOwner);
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;

	FHitResult HitResult;

	// is Bolck ?  sign EyeLocation,EndLocation to HirResult TraceStart, TraceEnd
	bool bIsBlock = GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, EndLocation, ECC_Visibility, QueryParams);
	if (bIsBlock)
	{
		UE_LOG(LogTemp, Warning, TEXT("SWeapon.cpp TraceLine Get block"));
		// do some thing when trace blocked
		FVector ShotDirection = EyeRotation.Vector();

		AActor* HitActor = HitResult.GetActor();
		UGameplayStatics::ApplyPointDamage(HitActor, 20.0f, ShotDirection, HitResult, MyOwner->GetInstigatorController(), this, DamageType);
		PlayImpactEffect(HitResult);
	}

	FVector	TraceEndLocation = bIsBlock ? HitResult.Location : EndLocation;
	PlayMuzzleEffect(TraceEndLocation);

	// Debug
	if (DebugWeaponDrawing > 0)
	{
		DrawDebugLine(GetWorld(), EyeLocation, EndLocation, FColor::Red, false, 1.0F);
	}
}

void ASWeapon::PlayMuzzleEffect(FVector TraceEndLocation)
{
	// Particles
	if (MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, SkeletaMeshComp, MuzzleSocketName);
	}
	// Trail
	FVector MuzzleLocation = SkeletaMeshComp->GetSocketLocation(MuzzleSocketName);
	UParticleSystemComponent* TraceComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, MuzzleLocation);
	if (TraceComp)
	{
		TraceComp->SetVectorParameter(TraceTargetName, TraceEndLocation);
	}
}

void ASWeapon::PlayImpactEffect(FHitResult HitResult)
{
	EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
	UParticleSystem* selectedEffect = nullptr;
	switch (SurfaceType)
	{
	case SURFACE_FLESHDEFALUT:
	case SURFACE_FLESHVULNERABLE:
		selectedEffect = FleshImpactEffect;
		break;
	default:
		selectedEffect = DefalutImpactEffect;
		break;
	}
	if (selectedEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), selectedEffect, HitResult.Location, HitResult.ImpactNormal.Rotation());
	}
}

void ASWeapon::PlayCameraShake()
{
	APawn* MyOwner = Cast<APawn>(GetOwner());
	if (FireCameraShake == nullptr || MyOwner == nullptr)
	{
		return;
	}
	APlayerController* PC = Cast<APlayerController>(MyOwner->GetController());
	if (PC)
	{
		PC->ClientStartCameraShake(FireCameraShake);
	}
}

