// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "EnemyProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "../ArcadeSHMUPPawn.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionProfileName(FName("OverlapAll"));
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetConstraintMode(EDOFMode::XYPlane);


	Particles = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particles"));
	Particles->AttachTo(RootComponent);
	Particles->bAutoActivate = true;
}


void AEnemyProjectile::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->ActorHasTag("Player"))
	{
		Cast<AArcadeSHMUPPawn>(OtherActor)->TakeDamage();
		Destroy();
	}
}

UParticleSystemComponent * AEnemyProjectile::GetParticles() const
{
	return Particles;
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		SetActorLocation(GetActorLocation() + GetActorForwardVector()*ProjectileInitialSpeed*DeltaTime);
	}
}

void AEnemyProjectile::SetProjectileSpeedModificator(float Modificator)
{
	ProjectileInitialSpeed *= Modificator;
}

