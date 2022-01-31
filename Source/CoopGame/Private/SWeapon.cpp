// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASWeapon::ASWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletaMeshComp = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	SkeletaMeshComp->SetupAttachment(RootComponent);

	MuzzleSocketName = "MuzzleSocket";
	TraceTargetName = "BeamEnd";
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASWeapon::Fire()
{
	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector EndLocation = EyeLocation + EyeRotation.Vector() * 10000;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(MyOwner);
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;


	FHitResult HitResult;
	// is Bolck ?  sign EyeLocation,EndLocation to HirResult TraceStart, TraceEnd
	if (GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, EndLocation, ECC_Visibility, QueryParams))
	{
		UE_LOG(LogTemp, Warning, TEXT("SWeapon.cpp TraceLine Get block"));
		// do some thing when trace blocked
		FVector ShotDirection = EyeRotation.Vector();

		AActor* HitActor = HitResult.GetActor();
		UGameplayStatics::ApplyPointDamage(HitActor, 20.0f, ShotDirection, HitResult, MyOwner->GetInstigatorController(), this, DamageType);

		// Particles
		if (MuzzleEffect)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, SkeletaMeshComp, MuzzleSocketName);
		}
		if (ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, HitResult.ImpactNormal.Rotation());
		}

		// Trail
		FVector MuzzleLocation = SkeletaMeshComp->GetSocketLocation(MuzzleSocketName);
		UParticleSystemComponent* TraceComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, MuzzleLocation);
		if (TraceComp)
		{
			TraceComp->SetVectorParameter(TraceTargetName, HitResult.Location);
		}

	}
	DrawDebugLine(GetWorld(), EyeLocation, EndLocation, FColor::Red, false, 1.0F);
}

// Called every frame
void ASWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
