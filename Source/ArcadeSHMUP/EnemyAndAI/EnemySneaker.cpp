// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySneaker.h"
#include "../ArcadeSHMUPPawn.h"

AEnemySneaker::AEnemySneaker()
{
	HitPoints = 50.f;

	PointsAwardedOnKill = 100;

	WeaponDropPriority = 2;
}

void AEnemySneaker::SetMaterialOpacityTo_Implementation(const float Value)
{
}

void AEnemySneaker::ReactToPlayer(AArcadeSHMUPPawn * Player)
{
	Player->TakeDamage();
}
