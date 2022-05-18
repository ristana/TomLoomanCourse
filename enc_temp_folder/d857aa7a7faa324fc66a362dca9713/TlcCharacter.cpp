// Fill out your copyright notice in the Description page of Project Settings.


#include "TlcCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATlcCharacter::ATlcCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ATlcCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATlcCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATlcCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATlcCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATlcCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);
}

void ATlcCharacter::MoveForward(const float Value)
{
	FRotator ControlRot = GetControlRotation();

	//only allow yaw to be passed
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	AddMovementInput(ControlRot.Vector(), Value);
}

void ATlcCharacter::MoveRight(const float Value)
{
	FRotator ControlRot = GetControlRotation();

	//only allow yaw to be passed
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// X = Fowrward
	// Y = Right
	// Z = Up
	
	//UKismetMathLibrary::GetRightVector(ControlRot);

	FVector RightVector = FRotationMatrix(ControlRot).GetScaleVector(EAxis::Y);


	//AddMovementInput(RightVector, Value);
}