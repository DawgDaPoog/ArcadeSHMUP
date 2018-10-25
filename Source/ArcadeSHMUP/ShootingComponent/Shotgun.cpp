// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Shotgun.h"
#include "Engine/World.h"

void AShotgun::Fire()
{
	if (Projectile)
	{
		GetWorld()->SpawnActor<AActor>(Projectile, GetActorForwardVector()*50.f, FRotator());
	}
}
