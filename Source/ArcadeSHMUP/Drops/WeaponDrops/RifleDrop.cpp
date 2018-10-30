// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "RifleDrop.h"
#include "ArcadeSHMUPPawn.h"
#include "ShootingComponent/ShootingComponent.h"

void ARifleDrop::NotifyPlayerPickedUp(AArcadeSHMUPPawn * Player)
{
	Player->GetShootingComponent()->OnWeaponPickup(2);
	Super::NotifyPlayerPickedUp(Player);
}
