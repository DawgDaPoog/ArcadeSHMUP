// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Weapon.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "ArcadeSHMUPGameMode.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionProfileName("OverlapAllDynamic");
	
	ParticlesOnShot = CreateDefaultSubobject<UParticleSystemComponent>(FName("OnShootParticles"));
	ParticlesOnShot->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

AProjectile* AWeapon::Fire()
{
	// Setting location to spawn at
	FVector Location = GetActorLocation() + GetActorForwardVector()*4.f;

	// Setting Z location at 250.f (Gameplay plane)
	Location.Z = 250.f;
	
	// Spwn transform
	FTransform SpawnLocation = FTransform(GetActorRotation(), Location, FVector(1.f));

	// Spawning and setting damage to projectile
	auto SpawnedProjectile = GetWorld()->SpawnActorDeferred<AProjectile>(Projectile, SpawnLocation);
	SpawnedProjectile->SetDamage(Damage);
	SpawnedProjectile->FinishSpawning(SpawnLocation);

	return SpawnedProjectile;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AWeapon::AttemptFire()
{
	// Firing and start reloading, if not reloading
	if (!bIsReloading) {
		Fire();
		SetReloadTimer();
	}
}

void AWeapon::Upgrade()
{
	//...
}

float AWeapon::GetKnockBackForce()
{
	return KnockbackForce;
}

void AWeapon::SetKnockBackForceModificator(float Modificator)
{
	KnockbackForceModificator *= Modificator;
	KnockbackForce *= KnockbackForceModificator;
}

float AWeapon::GetRateOfFire()
{
	return RateOfFire;
}

void AWeapon::SetRateOfFireModificator(float Modificator)
{
	RateOfFireModificator *= Modificator;
	RateOfFire *= RateOfFireModificator;
}

float AWeapon::GetProjectileSpeed()
{
	return ProjectileSpeed;
}

void AWeapon::SetProjectileSpeedModificator(float Modificator)
{
	ProjectileSpeedModificator *= Modificator;
	ProjectileSpeed *= ProjectileSpeedModificator;
}

float AWeapon::GetDamage()
{
	return Damage;
}

void AWeapon::SetDamageModificator(float Modificator)
{
	DamageModificator *= Modificator;
	Damage *= DamageModificator;
}

void AWeapon::BroadcastKnockback()
{
	OnFire.Broadcast(KnockbackForce);
}

void AWeapon::SetReloadTimer()
{
	bIsReloading = true;

	GetWorldTimerManager().SetTimer(ReloadTimer, this, &AWeapon::ReloadFinished, RateOfFire);
}

void AWeapon::ReloadFinished()
{
	bIsReloading = false;
}



