// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"
#include "components/StaticMeshComponent.h"
#include "Components/SHealthComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	HealthComp = CreateDefaultSubobject<USHealthComponent>(TEXT("HealthComp"));

	ExplodeRadius = 500.0f;
}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

	HealthComp->OnHealthChanged.AddDynamic(this, &AExplosiveBarrel::OnBarrelHealthChanged);
}

void AExplosiveBarrel::OnBarrelHealthChanged(USHealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Health <= 0)
	{
		if (bExpoled)
		{
			return;
		}
		Explode();
	}
}

void AExplosiveBarrel::Explode()
{
	bExpoled = true;
	MeshComp->SetMaterial(0, M_Exploded);
	MeshComp->AddImpulse(((FVector)(0, 0, 1000)));
	if (ExplodeEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeEffect, GetActorLocation(), FRotator::ZeroRotator, ((FVector)((3.0f))));
	}
	TArray<FHitResult> OutHits;
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Push(this);
	FVector BarrelLocation = GetActorLocation();
	FVector StartLocation = BarrelLocation;
	FVector EndLocation = BarrelLocation;
	FCollisionShape ExplodeShpere = FCollisionShape::MakeSphere(ExplodeRadius);

	DrawDebugSphere(GetWorld(), BarrelLocation, ExplodeShpere.GetSphereRadius(),20, FColor::Cyan, false,2.0f);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), 120.0f, BarrelLocation, ExplodeRadius, ExplodeDamageType, IgnoreActors, this);

	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, StartLocation, EndLocation, FQuat::Identity, ECC_WorldStatic, ExplodeShpere);
	if (isHit)
	{
		for (auto& Hit : OutHits)
		{
			UPrimitiveComponent* HitPrimComp = Hit.GetComponent();
			if (HitPrimComp)
			{
				HitPrimComp->AddRadialImpulse(BarrelLocation, 500.0f, 2000.0f, ERadialImpulseFalloff::RIF_Constant, true);
			}
		}
	}
}

