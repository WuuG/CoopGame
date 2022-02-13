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
#include "Net/UnrealNetwork.h"

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

	SetReplicates(true);

	NetUpdateFrequency = 66.0f;
	MinNetUpdateFrequency = 33.0f;
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
	
	// Client
	if (GetLocalRole() < ROLE_Authority)
	{
		ServerFire();
	}
	// Server
	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{
		return;
	}
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector EndLocation = EyeLocation + EyeRotation.Vector() * 1000000;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(MyOwner);
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;

	FHitResult HitResult;
	EPhysicalSurface SurfaceType = SurfaceType_Default;

	// is Bolck ?  sign EyeLocation,EndLocation to HirResult TraceStart, TraceEnd
	bool bIsBlock = GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, EndLocation, COLLISION_WEAPON, QueryParams);
	if (bIsBlock)
	{
		UE_LOG(LogTemp, Warning, TEXT("SWeapon.cpp TraceLine Get block"));
		// do some thing when trace blocked
		FVector ShotDirection = EyeRotation.Vector();

		float ActualDamage = BaseDamage;
		SurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
		if (SurfaceType == SURFACE_FLESHVULNERABLE)
		{
			ActualDamage *= 2.5;
		}
		AActor* HitActor = HitResult.GetActor();
		UGameplayStatics::ApplyPointDamage(HitActor, ActualDamage, ShotDirection, HitResult, MyOwner->GetInstigatorController(), this, DamageType);
		PlayImpactEffect(HitResult.ImpactPoint,SurfaceType);
	}

	FVector	TraceEndLocation = bIsBlock ? HitResult.Location : EndLocation;
	// 只有服务端需要改变， 因为在服务端,客户端的开火效果都能直接通过ServerFire()查看到. 而服务端的则通过这个值的改变来触发函数进行调用
	if (GetLocalRole() == ROLE_Authority)
	{
		HitScanTrace.TraceEnd = TraceEndLocation;
		HitScanTrace.SurfaceType = SurfaceType;
	}
	HitScanTrace.TraceEnd = TraceEndLocation;
	PlayMuzzleEffect(TraceEndLocation);

	LastFireTime = GetWorld()->TimeSeconds;

	// Debug
	if (DebugWeaponDrawing > 0)
	{
		DrawDebugLine(GetWorld(), EyeLocation, EndLocation, FColor::Red, false, 1.0F);
	}
}

// 虽然完成了同步，但是射击同一个位置的话，因为值没有改变所以无法触发这个函数
void ASWeapon::OnRep_HitScanTrace()
{
	PlayMuzzleEffect(HitScanTrace.TraceEnd);
	PlayImpactEffect(HitScanTrace.TraceEnd,HitScanTrace.SurfaceType);
}

void ASWeapon::ServerFire_Implementation()
{
	Fire();
}

bool ASWeapon::ServerFire_Validate()
{
	return true;
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

void ASWeapon::PlayImpactEffect(FVector ImpactLocation, EPhysicalSurface SurfaceType)
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
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), selectedEffect, ImpactLocation, FRotator::ZeroRotator);
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

void ASWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASWeapon, HitScanTrace, COND_SkipOwner);
}
