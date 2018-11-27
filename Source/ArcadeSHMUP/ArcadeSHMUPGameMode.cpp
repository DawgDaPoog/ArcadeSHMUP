// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ArcadeSHMUPGameMode.h"
#include "ArcadeSHMUPPawn.h"
#include "EnemyAndAI/SpawnPoint.h"
#include "TimerManager.h"


AArcadeSHMUPGameMode::AArcadeSHMUPGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = NULL;
	SpawnFrequency = 5.f;
	Intencity = 1;

	WaveSpawnSimpleMin = 2;
	WaveSpawnSimpleMax = 4;

	WaveSpawnAverageMin = 0;
	WaveSpawnAverageMax = 0;

	WaveSpawnAdvancedMin = 1;
	WaveSpawnAdvancedMax = 2;
}

void AArcadeSHMUPGameMode::BeginPlay()
{
	//Set a wave spawn timer
	GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &AArcadeSHMUPGameMode::WaveSpawn, 5.f, true, 5.f);


	WaveSpawnAdvancedMin = 1;
	WaveSpawnAdvancedMax = 2;
}

void AArcadeSHMUPGameMode::AddSpawnPoint(ASpawnPoint * SpawnPointToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Adding Spawn Point"));
	SpawnPoints.Add(SpawnPointToAdd);
}


void AArcadeSHMUPGameMode::WaveSpawn()
{
	if (SpawnPoints.Num() == 0) return;

	// Simple Spawn
	
	SpawnWaveType(1);
	SpawnWaveType(2);
	SpawnWaveType(3);
}

void AArcadeSHMUPGameMode::SpawnWaveType(int WaveIndex)
{
	// Getting the amount of array elements
	int SpawnPointAmount = SpawnPoints.Num();

	// Figuring out what types we are spawning
	int WaveSpawnMin = 0;
	int WaveSpawnMax = 0;
	switch (WaveIndex)
	{
	case 1:
		WaveSpawnMin = WaveSpawnSimpleMin;
		WaveSpawnMax = WaveSpawnSimpleMax;
		break;
	case 2:
		WaveSpawnMin = WaveSpawnAverageMin;
		WaveSpawnMax = WaveSpawnAverageMax;
		break;
	case 3:
		WaveSpawnMin = WaveSpawnAdvancedMin;
		WaveSpawnMax = WaveSpawnAdvancedMax;
		break;
	default:
		return;
	}
	//Early return if we have no need to spawn this type
	if (WaveSpawnMax == 0) return;

	//Setting the amount of enemies we want to spawn this wave for this type and choosing a random spawn point to spawn them
	int WaveSpawn = FMath::RandRange(WaveSpawnMin, WaveSpawnMax);
	for (int i = 0; i < WaveSpawn; i++)
	{
		StartSpawn(WaveIndex);
	}
}

void AArcadeSHMUPGameMode::StartSpawn(int WaveIndex)
{
	int SpawnerIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
	SpawnPoints[SpawnerIndex]->TrySpawn(WaveIndex);
}
