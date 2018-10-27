// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Rifle.h"
#include "Engine/World.h"
#include "Projectile.h"


ARifle::ARifle()
{
	RateOfFire = 1.5f;
	KnockbackForce = 40000.f;
	Damage = 50.f;
}

void ARifle::Fire()
{
	auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, FTransform(GetActorRotation(), GetActorLocation() + GetActorForwardVector()*5.f, FVector(1.f)));
	SpawnedProjectile->SetDamage(Damage);
	
	Super::Fire();
}
