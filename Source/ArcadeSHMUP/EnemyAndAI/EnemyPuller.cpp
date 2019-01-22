// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPuller.h"
#include "../ArcadeSHMUPPawn.h"
#include "Components/StaticMeshComponent.h"

AEnemyPuller::AEnemyPuller()
{

}

void AEnemyPuller::PullTowardsSelf(AArcadeSHMUPPawn * Player)
{
	// Getting the direction normal from player to this actor
	FVector DirectionNormal = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	// And setting force to apply to player
	FVector Force = DirectionNormal * PullForce;

	// Applying force
	if (Player)
	{
		Player->GetShipMeshComponent()->AddForce(Force);

		EmmitParticleEffectsTo(Player);
	}
}
