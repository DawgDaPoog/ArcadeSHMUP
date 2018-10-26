// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Shotgun.h"
#include "Engine/World.h"

AShotgun::AShotgun()
{
	RateOfFire = 1.f;
	KnockbackForce = 20000.f;
}

void AShotgun::Fire()
{
	if (Projectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning Projectile"));
		GetWorld()->SpawnActor<AActor>(Projectile, FTransform(GetActorRotation(),GetActorLocation()+GetActorForwardVector()*70.f, FVector(1.f)));
	}
	Super::Fire();
}
