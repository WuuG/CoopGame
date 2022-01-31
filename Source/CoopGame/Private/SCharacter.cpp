// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

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

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

