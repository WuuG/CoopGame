// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"
#include "components/StaticMeshComponent.h"
#include "Components/SHealthComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	RootComponent = MeshComp;

	HealthComp = CreateDefaultSubobject<USHealthComponent>(TEXT("HealthComp"));

	ExplodeRadius = 500.0f;
	ExplodeStrength = 1000.0f;

	SetReplicates(true);
	SetReplicateMovement(true);
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

void AExplosiveBarrel::PlayExplodeEffect()
{
	MeshComp->SetMaterial(0, M_Exploded);
	if (ExplodeEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeEffect, GetActorLocation(), FRotator::ZeroRotator, ((FVector)((3.0f))));
	}
}

void AExplosiveBarrel::Explode()
{

	// Client
	if (GetLocalRole() < ROLE_Authority)
	{
		Server_Explode();
		return;
	}
	// Server
	bExpoled = true;
	PlayExplodeEffect();
	FVector UpImpulse = FVector::UpVector * ExplodeStrength;
	MeshComp->AddImpulse(UpImpulse);
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
				HitPrimComp->AddRadialImpulse(BarrelLocation, 500.0f, ExplodeStrength, ERadialImpulseFalloff::RIF_Constant, true);
			}
		}
	}
}

void AExplosiveBarrel::OnRep_Exploded()
{	
	if (HealthComp->GetHealth() <= 0 && bExpoled)
	{
		PlayExplodeEffect();
	}
}

void AExplosiveBarrel::Server_Explode_Implementation()
{
	Explode();
}

bool AExplosiveBarrel::Server_Explode_Validate()
{
	return true;
}



void AExplosiveBarrel::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AExplosiveBarrel, bExpoled);
}
