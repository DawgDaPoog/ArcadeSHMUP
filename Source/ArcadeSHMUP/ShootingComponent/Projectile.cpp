// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EnemyAndAI/Enemy.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ProjectileMesh"));
	ProjectileMesh->SetCollisionProfileName("OverlapAll");
	ProjectileMesh->SetSimulatePhysics(true);

	RootComponent = ProjectileMesh;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileCurrentSpeed = ProjectileInitialSpeed;

	SetLifeSpan(3.f);
}

void AProjectile::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapped with enemy. Deal Damage"));
		ReactToEnemy(OtherActor);
	}
}

void AProjectile::ReactToEnemy(AActor * Enemy)
{
	Cast<AEnemy>(Enemy)->TakeDamage(Damage);
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

	if (bMoving)
	{
		Move(DeltaTime);
	}
}

void AProjectile::SetDamage(float DamageToSet)
{
	Damage = DamageToSet;
}

void AProjectile::SetProjectileSpeedModificator(float Modificator)
{
	ProjectileInitialSpeed *= Modificator;
	ProjectileMaxSpeed *= Modificator;
	ProjectileAcceleration *= Modificator;
}

void AProjectile::SetProjectileSizeModificator(float Modificator)
{
	SetActorScale3D(GetActorScale3D()*Modificator);
}

