// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TlcGameplayInterface.h"
#include "TlcItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class TOMLOOMANCOURSE_API ATlcItemChest : public AActor, public ITlcGameplayInterface

{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	ATlcItemChest();

	void Interact_Implementation(APawn* InstigatorPawn);

	UPROPERTY(EditAnywhere)
	float TargetPitch;
	

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
