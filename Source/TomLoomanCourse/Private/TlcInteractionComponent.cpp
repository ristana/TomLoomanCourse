// Fill out your copyright notice in the Description page of Project Settings.


#include "TlcInteractionComponent.h"
#include "TlcGameplayInterface.h"


// Sets default values for this component's properties
UTlcInteractionComponent::UTlcInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTlcInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTlcInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTlcInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);
	
	
	//FHitResult TraceHit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(TraceHit, EyeLocation, End, ObjectQueryParams);

	TArray<FHitResult> Hits;

	float Radius = 30.f;
	
	FCollisionShape Shape;
	Shape.SetSphere((Radius));
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for(auto Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (IsValid(HitActor))
		{
			if (HitActor->Implements<UTlcGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);

				ITlcGameplayInterface::Execute_Interact(HitActor, MyPawn);
				break;
			}
		}

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f, 0, 1.0f);
	}
	
	
	
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);

	
}