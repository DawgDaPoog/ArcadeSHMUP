// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "MachinegunDrop.h"
#include "ArcadeSHMUPPawn.h"
#include "ShootingComponent/ShootingComponent.h"

void AMachinegunDrop::NotifyPlayerPickedUp(AArcadeSHMUPPawn * Player)
{
	Player->GetShootingComponent()->OnWeaponPickup(1);
	Super::NotifyPlayerPickedUp(Player);
}
