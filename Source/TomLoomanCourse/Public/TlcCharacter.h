// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TlcCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UTlcInteractionComponent;
class UAnimMontage;

UCLASS()
class TOMLOOMANCOURSE_API ATlcCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

public:
	// Sets default values for this character's properties
	ATlcCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	UTlcInteractionComponent* InteractionComponent;

	FTimerHandle TimerHandle_PrimaryAttack;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UFUNCTION(BlueprintCallable)
	void DoJump();

	void MoveRight(const float Value);

	void MoveForward(const float Value);

	void PrimaryAttack();

	void PrimaryAttack_TimeElapsed();
	
	void PrimaryInteract();

};
