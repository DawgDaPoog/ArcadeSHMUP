// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "BlinkerRay.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "ArcadeSHMUPPawn.h"

ABlinkerRay::ABlinkerRay()
{
	Ray = CreateDefaultSubobject<UStaticMeshComponent>(FName("Ray"));
	Ray->SetCollisionProfileName(FName("OverlapAll"));
	Ray->SetGenerateOverlapEvents(true);
	Ray->SetConstraintMode(EDOFMode::XYPlane);

	ProjectileInitialSpeed = 0.f;

}

void ABlinkerRay::ActivateRay()
{
	// Set ray state to active
	bIsRayActive = true;

	// Put proper materials on ray to signify that it is activated and harmful
	Ray->SetMaterial(0, ActiveMaterial);

	// Check if we overlap with player
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for (auto Actor : OverlappingActors)
	{
		if (Actor->ActorHasTag("Player"))
		{
			// If we do, deal damage to him
			Cast<AArcadeSHMUPPawn>(Actor)->TakeDamage();
		}
	}
}

void ABlinkerRay::BeginPlay()
{
	Super::BeginPlay();

	Ray->SetMaterial(0, InactiveMaterial);
}

void ABlinkerRay::NotifyActorBeginOverlap(AActor * OtherActor)
{
	// If the ray is active
	if (bIsRayActive)
	{
		if (OtherActor->ActorHasTag("Player"))
		{
			// If we do, deal damage to him
			Cast<AArcadeSHMUPPawn>(OtherActor)->TakeDamage();
		}
	}
}
