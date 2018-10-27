// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Weapon.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Projectile.h"
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

void AWeapon::Fire()
{
	OnFire.Broadcast(KnockbackForce);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AWeapon::AttemptFire()
{
	if (!bIsReloading) {
		Fire();
		SetReloadTimer();
	}
}

void AWeapon::Upgrade()
{
	UE_LOG(LogTemp, Warning, TEXT("Upgrading Weapon"));
}

float AWeapon::GetKnockBackForce()
{
	return KnockbackForce;
}

void AWeapon::SetKnockBackForceModificator(float Modificator)
{
	KnockbackForceModificator *= Modificator;
}

float AWeapon::GetRateOfFire()
{
	return RateOfFire;
}

void AWeapon::SetRateOfFireModificator(float Modificator)
{
	RateOfFireModificator *= Modificator;
}

float AWeapon::GetProjectileSpeed()
{
	return ProjectileSpeed;
}

void AWeapon::SetProjectileSpeedModificator(float Modificator)
{
	ProjectileSpeedModificator *= Modificator;
}

float AWeapon::GetDamage()
{
	return Damage;
}

void AWeapon::SetDamageModificator(float Modificator)
{
	DamageModificator *= Modificator;
}

float AWeapon::GetProjectileSizeModificator()
{
	return ProjectileSizeModificator;
}

void AWeapon::SetProjectileSizeModificator(float Modificator)
{
	ProjectileSizeModificator *= Modificator;
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



