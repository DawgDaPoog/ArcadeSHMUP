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
	TArray<class ASpawnPoint*> SpawnPoints;

	float SpawnFrequency;

	int WaveSpawnSimpleMin;
	int WaveSpawnSimpleMax;

	int WaveSpawnAverageMin;
	int WaveSpawnAverageMax;

	int WaveSpawnAdvancedMin;
	int WaveSpawnAdvancedMax;

	int Intencity;

	void WaveSpawn();

	void SpawnWaveType(int WaveIndex);

	UFUNCTION()
	void StartSpawn(int WaveIndex);

	FTimerHandle WaveTimerHandle;
public:
	AArcadeSHMUPGameMode();

	virtual void BeginPlay() override;

	void AddSpawnPoint(class ASpawnPoint* SpawnPointToAdd);

	
};



