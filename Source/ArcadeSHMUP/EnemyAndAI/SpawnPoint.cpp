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
	SpawnEnemyOfType(CategoryIndex);
}

bool ASpawnPoint::SpawnEnemyOfType(int CategoryIndex)
{
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
		return false;
	}
	if (EnemiesArray.Num() == 0)
	{
		return false;
	}
	int SpawnIndex = FMath::RandRange(0, EnemiesArray.Num() - 1);

	UE_LOG(LogTemp, Warning, TEXT("Spawned an enemy of type %i at %s"), CategoryIndex, *GetName());

	if (SpawnerActor)
	{
		auto SpawnedSpawnerActor = GetWorld()->SpawnActorDeferred<ASpawnerActor>(SpawnerActor, GetActorTransform());
		SpawnedSpawnerActor->SetDesiredSpawningActor(EnemiesArray[SpawnIndex]);
		SpawnedSpawnerActor->FinishSpawning(GetActorTransform());
	}
	//GetWorld()->SpawnActor<AEnemy>(EnemiesArray[SpawnIndex], GetActorTransform());
	return true;
}

