// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "ShotgunDrop.h"
#include "ArcadeSHMUPPawn.h"
#include "ShootingComponent/ShootingComponent.h"

void AShotgunDrop::NotifyPlayerPickedUp(AArcadeSHMUPPawn* Player)
{
	MessageToForward = FString("You picked up an Shotgun!");
	Player->GetShootingComponent()->OnWeaponPickup(0);
	Super::NotifyPlayerPickedUp(Player);
}
