// Fill out your copyright notice in the Description page of Project Settings.


#include "TlcExplosiveBarrel.h"

#include "TlcMagicProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ATlcExplosiveBarrel::ATlcExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup Static Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetCollisionProfileName("PhysicsActor");
	
	//Setup New Root
	RootComponent = StaticMesh;

	//Setup Radial Force Comp
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(StaticMesh);
	RadialForceComponent->SetAutoActivate(false);
	RadialForceComponent->Radius = 700.f;
	RadialForceComponent->ImpulseStrength = 2000.f;
	RadialForceComponent->bImpulseVelChange = true;
	
}

// Called when the game starts or when spawned
void ATlcExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATlcExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// On Hit
void ATlcExplosiveBarrel::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);


	if(IsValid(Other))
	{
		if(AActor* MagicProjectile = Cast<ATlcMagicProjectile>(Other))
		{
			RadialForceComponent->FireImpulse();
		}
	}

	//RadialForceComponent->FireImpulse();
}
