// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArcadeSHMUPGameMode.generated.h"

UCLASS(MinimalAPI)
class AArcadeSHMUPGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	// Spawn points that are to be used to spawn new enemies
	TArray<class ASpawnPoint*> SpawnPoints;

	// How frequently enemies will spawn
	float SpawnFrequency;

	// Amount of simple enemies that are to be spawned in a given wave
	int WaveSpawnSimpleMin;
	int WaveSpawnSimpleMax;

	// Amount of average enemies that are to be spawned in a given wave
	int WaveSpawnAverageMin;
	int WaveSpawnAverageMax;

	// Amount of advanced enemies that are to be spawned in a given wave
	int WaveSpawnAdvancedMin;
	int WaveSpawnAdvancedMax;

	// Intencity level that decides the amounts of 
	int Intencity;

	// Spawning a wave of enemies (Telling the spawn points to attempt spawning)
	void WaveSpawn();

	// Determine how much enemies we need to spawn in a given wave index and call upon random spawn points to do so
	void SpawnWaveType(int WaveIndex);

	// Calling spawn on SpawnPoint
	UFUNCTION()
	void StartSpawn(int WaveIndex);

	// Timer to handle repeated spawning
	FTimerHandle WaveTimerHandle;
public:
	AArcadeSHMUPGameMode();

	virtual void BeginPlay() override;

	// Called on SpawnPoint's begin play, asking to add itself onto the SpawnPoints array
	void AddSpawnPoint(class ASpawnPoint* SpawnPointToAdd);

	
};



