// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Drop.h"
#include "../ArcadeSHMUPPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ADrop::ADrop()
{
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

void ADrop::NotifyPlayerPickedUp(AArcadeSHMUPPawn* Player)
{
	// Default behavior on pickup
	Destroy();
}

void ADrop::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	// If it overlapped with the player, interract
	if (OtherActor->ActorHasTag("Player"))
	{
		NotifyPlayerPickedUp(Cast<AArcadeSHMUPPawn>(OtherActor));
	}
}

