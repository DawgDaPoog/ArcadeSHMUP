// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ProjectileMesh"));
	ProjectileMesh->SetCollisionProfileName("OverlapAll");
	RootComponent = ProjectileMesh;

	
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{
		ReactToEnemy(OtherActor);
	}
}

void AProjectile::ReactToEnemy(AActor * Enemy)
{
	// Do something to enemy
}

void AProjectile::Move(float DeltaTime)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector()*ProjectileCurrentSpeed*DeltaTime);

	if (ProjectileCurrentSpeed >= ProjectileMaxSpeed)
	{
		ProjectileCurrentSpeed = ProjectileMaxSpeed;
	}
	else
	{
		ProjectileCurrentSpeed += ProjectileAcceleration * DeltaTime;
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
	

}

void AProjectile::SetDamage(float DamageToSet)
{
	Damage = DamageToSet;
}

