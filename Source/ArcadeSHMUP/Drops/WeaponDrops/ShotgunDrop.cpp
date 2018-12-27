// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "ShotgunDrop.h"
#include "ArcadeSHMUPPawn.h"
#include "ShootingComponent/ShootingComponent.h"

void AShotgunDrop::NotifyPlayerPickedUp(AArcadeSHMUPPawn* Player)
{
	Player->GetShootingComponent()->OnWeaponPickup(0);
	Super::NotifyPlayerPickedUp(Player);
}
