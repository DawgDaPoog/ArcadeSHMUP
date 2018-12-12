// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "ArcDrop.h"
#include "ArcadeSHMUPPawn.h"
#include "ShootingComponent/ShootingComponent.h"

void AArcDrop::NotifyPlayerPickedUp(AArcadeSHMUPPawn * Player)
{
	MessageToForward = FString("You picked up an Arc!");
	Player->GetShootingComponent()->OnWeaponPickup(5);
	Super::NotifyPlayerPickedUp(Player);
}
