// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SHealthComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
USHealthComponent::USHealthComponent()
{
	DefalutHealth = 100;

	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() < ROLE_Authority)
	{
		return;
	}

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		Health = DefalutHealth;
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &USHealthComponent::HandleTakeAnyDamage);
	}
}

void USHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Health < 0.0f)
	{
		return;
	}
	Health = FMath::Clamp(Health - Damage, 0.0f, DefalutHealth);

	UE_LOG(LogTemp, Warning, TEXT("Health Change: %s"), *FString::SanitizeFloat(Health));

	DamageInfo.Damage	 = Damage;
	DamageInfo.DamageType = DamageType;
	DamageInfo.InstigatedBy = InstigatedBy;
	DamageInfo.DamageCauser = DamageCauser;

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
}

void USHealthComponent::OnRep_HealthChange()
{
	OnHealthChanged.Broadcast(this, Health,DamageInfo.Damage ,DamageInfo.DamageType, DamageInfo.InstigatedBy,DamageInfo.DamageCauser);
}

float USHealthComponent::GetHealth()
{
	return Health;
}


void USHealthComponent::Heal(float HealtAmount, AActor* OtherActor /*= nullptr*/)
{
	if (Health <= 0 || HealtAmount < 0)
	{
		return;
	}
	Health = FMath::Clamp((Health + HealtAmount), 0.0f, DefalutHealth);

	UE_LOG(LogTemp, Log, TEXT("Health Change: %s (%s)"), *FString::SanitizeFloat(Health), *FString::SanitizeFloat(HealtAmount));
	
	OnHealthChanged.Broadcast(this, Health, -HealtAmount, nullptr, nullptr, OtherActor);
}

void USHealthComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(USHealthComponent, Health);
}
