// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STrackerBot.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Components/SHealthComponent.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
ASTrackerBot::ASTrackerBot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCanEverAffectNavigation(false);
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	HealtComp = CreateDefaultSubobject<USHealthComponent>(TEXT("HealthComp"));

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereRaius = 200.0f;
	SphereComp->SetSphereRadius(SphereRaius);
	SphereComp->SetupAttachment(MeshComp);

	MoveForce = 500;
	DistanceOfFindPath = 100.0f;
	bUseVelocityChange = true;

	bExploded = false;
	bStartSelfDestructed = false;
	ExplosionDamage = 50.0f;
	ExplosionRadius = 200.0f;
	ExplosionFullDamage = true;
	SelfDestructDamage = 20.0f;
	DamageSelfInterval = 1;
}

// Called when the game starts or when spawned
void ASTrackerBot::BeginPlay()
{
	Super::BeginPlay();

	NextPathPoint = GetNextPathPoint();
	HealtComp->OnHealthChanged.AddDynamic(this, &ASTrackerBot::HandleTakeDamage);
}

FVector ASTrackerBot::GetNextPathPoint()
{
	ACharacter* PlayerPawn = UGameplayStatics::GetPlayerCharacter(this, 0);
	UNavigationPath* NavPath = UNavigationSystemV1::FindPathToActorSynchronously(this, GetActorLocation(), PlayerPawn);

	if (NavPath && NavPath->PathPoints.Num() > 1)
	{
		return NavPath->PathPoints[1];
	}
	return  GetActorLocation();
}

void ASTrackerBot::HandleTakeDamage(USHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (MatInst == nullptr)
	{
		MatInst = MeshComp->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MeshComp->GetMaterial(0));
	}
	if (MatInst)
	{
		MatInst->SetScalarParameterValue("LastDamageTaken", GetWorld()->TimeSeconds);
	}
	if (Health <= 0)
	{
		SelfDestruct();
	}

	UE_LOG(LogTemp, Log, TEXT("Health %s of %s"), *FString::SanitizeFloat(Health), *GetName());
}

void ASTrackerBot::SelfDestruct()
{
	if (bExploded)
	{
		return;
	}
	bExploded = true;

	PlayExplosionEffect();
	SetFakeDestruct();

	if (GetLocalRole() < ROLE_Authority)
	{
		return;
	}
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	UGameplayStatics::ApplyRadialDamage(this, ExplosionDamage, GetActorLocation(), ExplosionRadius, nullptr, IgnoreActors, this,nullptr, ExplosionFullDamage);

	DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosionRadius, 32, FColor::Red, false, 2.0f);
}

void ASTrackerBot::PlayExplosionEffect()
{
	if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	}
	UGameplayStatics::PlaySoundAtLocation(this,ExplodeSound, GetActorLocation());
}

void ASTrackerBot::DamageSelf()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		return;
	}
	UGameplayStatics::ApplyDamage(this, SelfDestructDamage, nullptr, this, nullptr);
}

void ASTrackerBot::SetFakeDestruct()
{
	MeshComp->SetVisibility(false, true);
	MeshComp->SetSimulatePhysics(false);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(2.0f);
}

// Called every frame
void ASTrackerBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bExploded)
	{
		return;
	}

	float DistanceToTarget =(NextPathPoint - GetActorLocation()).Size();
	if (DistanceToTarget <= DistanceOfFindPath)
	{
		NextPathPoint = GetNextPathPoint();
	}
	else
	{
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();
		ForceDirection *= MoveForce;

		MeshComp->AddForce(ForceDirection, NAME_None,bUseVelocityChange);
		DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), NextPathPoint, 12, FColor::Yellow);
	}

//	DrawDebugSphere(GetWorld(), NextPathPoint, 20.0f, 32, FColor::Green);
}

void ASTrackerBot::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (bStartSelfDestructed || bExploded)
	{
		return;
	}
	UGameplayStatics::SpawnSoundAttached(SelfDestructSound, RootComponent);
	GetWorldTimerManager().SetTimer(TimerHandler_StartSelfConstruct,this,&ASTrackerBot::DamageSelf,DamageSelfInterval, true, 0.0f);
	bStartSelfDestructed = true;
}

