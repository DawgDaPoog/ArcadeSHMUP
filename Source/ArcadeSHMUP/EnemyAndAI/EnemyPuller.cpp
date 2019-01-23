// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPuller.h"
#include "../ArcadeSHMUPPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

AEnemyPuller::AEnemyPuller()
{
	HitPoints = 70.f;

	PointsAwardedOnKill = 100;

	WeaponDropPriority = 2;
}

void AEnemyPuller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If we have player set up, set rotation to face him
	if (FocusedOnPlayer)
	{
		FRotator RotationToPlayer = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FocusedOnPlayer->GetActorLocation());
		SetActorRotation(RotationToPlayer);

		// Clearing the focus
		FocusedOnPlayer = nullptr;
	}
}

void AEnemyPuller::PullTowardsSelf(APawn * Player, float ForceModificator)
{
	// Setting a player to focus on
	if (Player)
	{
		FocusedOnPlayer = Player;

		FVector PlayerLocation = Player->GetActorLocation();
		FVector MyLocation = GetActorLocation();

		// Getting the direction normal from player to this actor
		FVector DirectionNormal = (MyLocation - PlayerLocation).GetSafeNormal();

		// And setting force to apply to player
		FVector Force = DirectionNormal * PullForce * ForceModificator;

		// Applying force
		Cast<AArcadeSHMUPPawn>(Player)->GetShipMeshComponent()->AddForce(Force);

		EmmitParticleEffectsTo(Player);
	
	}
}

void AEnemyPuller::ReactToPlayer(AArcadeSHMUPPawn * Player)
{
	Player->TakeDamage();
}
