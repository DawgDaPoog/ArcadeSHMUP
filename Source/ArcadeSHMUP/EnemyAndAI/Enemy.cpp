// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "../ArcadeSHMUPPawn.h"
#include "ArcadeSHMUPGameMode.h"
#include "Engine/World.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleEmitter.h"
#include "Particles/ParticleSystem.h"
// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Default mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	RootComponent = Mesh;
	Mesh->SetConstraintMode(EDOFMode::XYPlane);
	Mesh->SetSimulatePhysics(true);

	// Adding a tag for gameplay purpose
	Tags.Add(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Telling the game mode that we got spawned.
	
}

void AEnemy::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
	// When colliding with a player, react to him (Try to deal damage)
	if (Other->ActorHasTag("Player"))
	{
		ReactToPlayer(Cast<AArcadeSHMUPPawn>(Other));
	}
}

void AEnemy::NotifyActorBeginOverlap(AActor * OtherActor)
{
	// Upon overlapping w/ player, react to him
	if (OtherActor->ActorHasTag("Player"))
	{
		ReactToPlayer(Cast<AArcadeSHMUPPawn>(OtherActor));
	}
}

void AEnemy::ReactToPlayer(AArcadeSHMUPPawn * Player)
{
	// Take damage when reacting to a player
	Player->TakeDamage();
}

void AEnemy::SequenceDestroy()
{
	// Broadcast destruction to gamemode
	Cast<AArcadeSHMUPGameMode>(GetWorld()->GetAuthGameMode())->ReactToEnemyDeath(PointsAwardedOnKill, GetActorLocation(), WeaponDropPriority, ModificationDropPriority);

	if (ParticlesOnDeath)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticlesOnDeath, GetActorLocation(), FRotator(0.f));
	}

	Destroy();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::TakeDamage(float Damage)
{
	HitPoints -= Damage;

	if (HitPoints <= 0.f)
	{
		SequenceDestroy();
	}
}



