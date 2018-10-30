// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Drop.h"
#include "../ArcadeSHMUPPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ADrop::ADrop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetCollisionProfileName("OverlapAllDynamic");
	RootComponent = Mesh;

	Glow = CreateDefaultSubobject<UParticleSystemComponent>(FName("Glow"));
	Glow->bAutoActivate = true;
	Glow->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADrop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADrop::NotifyPlayerPickedUp(AArcadeSHMUPPawn* Player)
{
	Destroy();
}

void ADrop::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->ActorHasTag("Player"))
	{
		NotifyPlayerPickedUp(Cast<AArcadeSHMUPPawn>(OtherActor));
	}
}

