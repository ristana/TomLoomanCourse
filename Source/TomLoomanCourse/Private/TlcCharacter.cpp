// Fill out your copyright notice in the Description page of Project Settings.


#include "TlcCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "TlcInteractionComponent.h"

// Sets default values
ATlcCharacter::ATlcCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 450.f;
		
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeTransform(FTransform(FRotator(0, 0, 0), FVector(0, 0, 40), FVector(0, 0, 0)));

	InteractionComponent = CreateDefaultSubobject<UTlcInteractionComponent>("InteractionComponent");

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

	// -- rotation visualization -- //
	const float LineArrowSize = 100.0f;
	const float LineThickness = 5.0f;

	FVector LineStart = GetActorLocation();

	//offset to be right of pawn
	LineStart += GetActorRightVector() * 100.0f;

	//SetLine end in direction of actors forward vector
	const FVector ForwardOffset = GetActorForwardVector() * 100.f;
	const FVector ActorDirection_LineEnd = LineStart + ForwardOffset;

	//Draw Actor Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, LineArrowSize, FColor::Yellow, false, 0.0f, 0, LineThickness);

	FVector ControlDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);

	//Draw controller direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControlDirection_LineEnd, LineArrowSize, FColor::Green, false, 0.0f, 0, LineThickness);
}

// Called to bind functionality to input
void ATlcCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATlcCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATlcCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ATlcCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ATlcCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATlcCharacter::DoJump);
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

	// X = Forward
	// Y = Right
	// Z = Up
	
	FVector RightVector = UKismetMathLibrary::GetRightVector(ControlRot);

	AddMovementInput(RightVector, Value);
}

void ATlcCharacter::PrimaryAttack()
{
	if (!this->GetCurrentMontage())
	{
		PlayAnimMontage(AttackAnim);

		GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ATlcCharacter::PrimaryAttack_TimeElapsed, 0.2f);
	}

	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void ATlcCharacter::PrimaryAttack_TimeElapsed()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FTransform SpawnTransform = FTransform(GetControlRotation(), HandLocation, FVector3d(1.0, 1.0, 1.0));

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParameters);
}

void ATlcCharacter::PrimaryInteract()
{
	if(InteractionComponent)
	{
		InteractionComponent->PrimaryInteract();
	}
}

void ATlcCharacter::DoJump()
{
	this->Jump();
}