// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "LazerDrop.h"
#include "ArcadeSHMUPPawn.h"
#include "ShootingComponent/ShootingComponent.h"

void ALazerDrop::NotifyPlayerPickedUp(AArcadeSHMUPPawn * Player)
{
	MessageToForward = FString("You picked up a Lazer!");
	Player->GetShootingComponent()->OnWeaponPickup(3);
	Super::NotifyPlayerPickedUp(Player);
}
