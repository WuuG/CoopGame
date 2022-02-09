// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SWeapon.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// 设置视角组件， 并跟随人物旋转
	SprintArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArmComp"));
	SprintArmComp->bUsePawnControlRotation = true;
	SprintArmComp->SetupAttachment(RootComponent);

	ThirdViewCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("ThiredViewCameraComp"));
	ThirdViewCameraComp->SetupAttachment(SprintArmComp);

	FirstViewCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstViewCameraComp"));
	FirstViewCameraComp->bUsePawnControlRotation = true;
	FirstViewCameraComp->SetupAttachment(RootComponent);

	CurrentViewCameraComp = ThirdViewCameraComp;

	// enable courch
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	
	// Run Action
	CharacterMovementComp = GetCharacterMovement();
	WalkSpeed = 300.0f;
	RunSpeed = 600.0f;

	// Zoom
	ZoomedFov = 50.0f;
	ZoomInterpSpeed = 60.0f;

	// Weapon
	WeaponAttachSocketName = "WeaponLocationSocket";

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefalutFov = ThirdViewCameraComp->FieldOfView;
	CreateWeapon();
}

void ASCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void ASCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void ASCharacter::BeginCrouch()
{
	ASCharacter::Crouch();
}

void ASCharacter::EndCrouch()
{
	ASCharacter::UnCrouch();
}

void ASCharacter::BeginRun()
{
	CharacterMovementComp->MaxWalkSpeed = RunSpeed;
}

void ASCharacter::EndRun()
{
	CharacterMovementComp->MaxWalkSpeed = WalkSpeed;
}



void ASCharacter::SwitchViewFromTwoCamera()
{
	if (CurrentViewCameraComp == ThirdViewCameraComp)
	{
		CurrentViewCameraComp = FirstViewCameraComp;
		ThirdViewCameraComp->Deactivate();
		FirstViewCameraComp->Activate();
	}
	else
	{
		CurrentViewCameraComp = ThirdViewCameraComp;
		FirstViewCameraComp->Deactivate();
		ThirdViewCameraComp->Activate();
	}
}

void ASCharacter::BeginZoom()
{
	bWantToZoom = true;
}

void ASCharacter::EndZoom()
{
	bWantToZoom = false;
}

void ASCharacter::FovZoom(float DeltaTime)
{
		float TargetFov = bWantToZoom ? ZoomedFov : DefalutFov;
		float NewFov = FMath::FInterpTo(CurrentViewCameraComp->FieldOfView, TargetFov, DeltaTime, ZoomInterpSpeed);
		CurrentViewCameraComp->SetFieldOfView(NewFov);
}

void ASCharacter::CreateWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Create Weapon"));
	if (StarterWeaponClass == nullptr)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	CurrentWeapon =	GetWorld()->SpawnActor<ASWeapon>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponAttachSocketName);
	}

}

void ASCharacter::Fire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Fire();
	}
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FovZoom(DeltaTime);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// bind Move KeyBoard
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Pitch", this, &ASCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);
	
	// bind action
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASCharacter::EndCrouch);
	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ASCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASCharacter::BeginRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASCharacter::EndRun);

	PlayerInputComponent->BindAction("SwitchView", IE_Pressed, this, &ASCharacter::SwitchViewFromTwoCamera);
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ASCharacter::BeginZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &ASCharacter::EndZoom);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASCharacter::Fire);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	if (CurrentViewCameraComp == ThirdViewCameraComp)
	{
		return ThirdViewCameraComp->GetComponentLocation();
	}
	else
	{
		return FirstViewCameraComp->GetComponentLocation();
	}
	return GetActorLocation() + FVector(0.f,0.f,BaseEyeHeight);
}

