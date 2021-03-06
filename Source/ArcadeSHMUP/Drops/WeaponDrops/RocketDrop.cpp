// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "RocketDrop.h"
#include "ArcadeSHMUPPawn.h"
#include "ShootingComponent/ShootingComponent.h"

void ARocketDrop::NotifyPlayerPickedUp(AArcadeSHMUPPawn * Player)
{
	Player->GetShootingComponent()->OnWeaponPickup(4);
	Super::NotifyPlayerPickedUp(Player);
}
