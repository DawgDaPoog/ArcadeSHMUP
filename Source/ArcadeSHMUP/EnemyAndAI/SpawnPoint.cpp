// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "SpawnPoint.h"
#include "Engine/World.h"
#include "ArcadeSHMUPGameMode.h"
#include "Enemy.h"
#include "SpawnerActor.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	// Finding current game mode and asking to add this a spawn point to array
	if (Cast<AArcadeSHMUPGameMode>(GetWorld()->GetAuthGameMode()))
	{
		Cast<AArcadeSHMUPGameMode>(GetWorld()->GetAuthGameMode())->AddSpawnPoint(this);
	}
	
}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnPoint::TrySpawn(int CategoryIndex)
{
	// Creating an array and figuring out which from which enemy array we need to spawn an enemy
	TArray<TSubclassOf<AEnemy>> EnemiesArray;
	if (CategoryIndex == 1)
	{
		EnemiesArray = SimpleEnemies;
	}
	else if (CategoryIndex == 2)
	{
		EnemiesArray = AverageEnemies;
	}
	else if (CategoryIndex == 3)
	{
		EnemiesArray = AdvancedEnemies;
	}
	else
	{
		// Early return if the index was invalid
		return;
	}

	if (EnemiesArray.Num() == 0)
	{
		// Early return if we have nothing in the array that we have assumed
		return;
	}

	// Taking a random index from the array to spawn
	int SpawnIndex = FMath::RandRange(0, EnemiesArray.Num() - 1);

	// If we have an actor set, spawn it and tell it which enemy we need it to eventually spawn
	if (SpawnerActor)
	{
		auto SpawnedSpawnerActor = GetWorld()->SpawnActorDeferred<ASpawnerActor>(SpawnerActor, GetActorTransform());
		SpawnedSpawnerActor->SetDesiredSpawningActor(EnemiesArray[SpawnIndex]);
		SpawnedSpawnerActor->FinishSpawning(GetActorTransform());
	}
}



