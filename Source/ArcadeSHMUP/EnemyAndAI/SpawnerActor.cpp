// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "SpawnerActor.h"
#include "TimerManager.h"
#include "Enemy.h"
#include "Engine/World.h"

// Sets default values
ASpawnerActor::ASpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnerActor::BeginPlay()
{
	Super::BeginPlay();

	// Setting a repeating timer to check for collision and spawn an enemy if we have none
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &ASpawnerActor::TrySpawnAndDestroy, 1.f, true, 1.f);
}

// Called every frame
void ASpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnerActor::SetDesiredSpawningActor(TSubclassOf<class AEnemy> Enemy)
{
	EnemyToSpawn = Enemy;
}

void ASpawnerActor::TrySpawnAndDestroy()
{
	// Getting overlapping actors
	TSet<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	// For every overlapping actor
	for (auto OverlappingActor : OverlappingActors)
	{
		// Check if it is an enemy or a player
		if (OverlappingActor->ActorHasTag("Player") || OverlappingActor->ActorHasTag("Enemy"))
		{
			// If it is an enemy, don't spawn and return
			return;
		}
	}
	// If we didn't find any overlapping with player or enemy, spawn an enemy
	auto SpawnedEnemy = GetWorld()->SpawnActorDeferred<AEnemy>(EnemyToSpawn, GetActorTransform());
	//SpawnedEnemy->NotifyGameModeOfEnemySpawned();
	// TODO Set the modifiers on enemies here... When you have finished the system that is
	SpawnedEnemy->FinishSpawning(GetActorTransform());

	// Destroying this actor to end checking for collision and spawning
	Destroy();
}

