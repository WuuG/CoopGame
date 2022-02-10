// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShake.h"
#include "CoopGame/CoopGame.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "TimerManager.h"

using namespace EMyEnum;

static int32 DebugWeaponDrawing = 0;
FAutoConsoleVariableRef CVARDebugWeaponDrawing(TEXT("COOP.DebugWeapons"), DebugWeaponDrawing, TEXT("Draw Debug Lines for Weapon"), ECVF_Cheat);

// Sets default values
ASWeapon::ASWeapon()
{
	SkeletaMeshComp = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	SkeletaMeshComp->SetupAttachment(RootComponent);

	MuzzleSocketName = "MuzzleSocket";
	TraceTargetName = "BeamEnd";
	
	bIsMulFireMode = false;

	FireMode = EFireMode::SemiAuto;
}

void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	TimeBetweenShots = 60 / RateOfFire;
	// prevent can't shot when beginplay
	LastFireTime = -TimeBetweenShots;
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
	bool bIsBlock = GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, EndLocation, COLLISION_WEAPON, QueryParams);
	if (bIsBlock)
	{
		UE_LOG(LogTemp, Warning, TEXT("SWeapon.cpp TraceLine Get block"));
		// do some thing when trace blocked
		FVector ShotDirection = EyeRotation.Vector();

		float ActualDamage = BaseDamage;
		EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
		if (SurfaceType == SURFACE_FLESHVULNERABLE)
		{
			ActualDamage *= 2.5;
		}
		AActor* HitActor = HitResult.GetActor();
		UGameplayStatics::ApplyPointDamage(HitActor, ActualDamage, ShotDirection, HitResult, MyOwner->GetInstigatorController(), this, DamageType);
		PlayImpactEffect(HitResult,SurfaceType);
	}

	FVector	TraceEndLocation = bIsBlock ? HitResult.Location : EndLocation;
	PlayMuzzleEffect(TraceEndLocation);

	LastFireTime = GetWorld()->TimeSeconds;

	// Debug
	if (DebugWeaponDrawing > 0)
	{
		DrawDebugLine(GetWorld(), EyeLocation, EndLocation, FColor::Red, false, 1.0F);
	}
}

void ASWeapon::StartFire()
{
	if (FireMode == EFireMode::FullyAuto)
	{
		float FirstDelay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.0f);
		GetWorldTimerManager().SetTimer(TimerHandler_TimeBetweenShots, this, &ASWeapon::Fire,TimeBetweenShots, true, FirstDelay);
	}
	if (FireMode == EFireMode::SemiAuto)
	{
		float FirstDelay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.0f);
		if (FirstDelay > 0)
		{
			return;
		}
		Fire();
	}
}

void ASWeapon::StopFire()
{
	if (FireMode == EFireMode::FullyAuto)
	{
		GetWorldTimerManager().ClearTimer(TimerHandler_TimeBetweenShots);
	}
}


void ASWeapon::SwitchMode()
{
	if (!bIsMulFireMode)
	{
		return;
	}
	switch (FireMode)
	{
	case EFireMode::SemiAuto:
		FireMode = EFireMode::FullyAuto;
		break;
	case EFireMode::FullyAuto:
		FireMode = EFireMode::SemiAuto;
		break;
	default:
		FireMode = EFireMode::SemiAuto;
		break;
	}
	OnFireModeChange(FireMode);
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

void ASWeapon::PlayImpactEffect(FHitResult HitResult, EPhysicalSurface SurfaceType)
{
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

