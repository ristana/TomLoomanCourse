// Fill out your copyright notice in the Description page of Project Settings.


#include "TlcItemChest.h"

// Sets default values
ATlcItemChest::ATlcItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;
	
	LidMesh = CreateDefaultSubobject <UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110;
}


void ATlcItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

// Called when the game starts or when spawned
void ATlcItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATlcItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

