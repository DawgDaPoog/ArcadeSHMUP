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

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyProjectile::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		Cast<AArcadeSHMUPPawn>(OtherActor)->TakeDamage();
		Destroy();
	}
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

