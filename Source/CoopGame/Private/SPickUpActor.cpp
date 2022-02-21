// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUpActor.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "SPowerUpActor.h"

// Sets default values
ASPickUpActor::ASPickUpActor()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetSphereRadius(75.0f);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = SphereComp;

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(64, 75, 75);
	DecalComp->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	DecalComp->SetupAttachment(RootComponent);

	CoolDownDuration = 10.0f;
}

// Called when the game starts or when spawned
void ASPickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
	Respawn();
}

void ASPickUpActor::Respawn()
{

	if (PowerUpActorClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		PowerUpInst = GetWorld()->SpawnActor<ASPowerUpActor>(PowerUpActorClass,GetTransform(), SpawnParams);
	}
}

void ASPickUpActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (PowerUpInst)
	{
		PowerUpInst->ActivatePowerup(OtherActor);
		PowerUpInst = nullptr;
		FTimerHandle TimerHandle_RespawnTimer;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ASPickUpActor::Respawn, CoolDownDuration);
	}
}

