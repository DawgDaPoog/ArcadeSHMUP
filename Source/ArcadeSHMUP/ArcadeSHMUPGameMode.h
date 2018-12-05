// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ScoreSystemSaveGame.h"
#include "ArcadeSHMUPGameMode.generated.h"


UCLASS(MinimalAPI)
class AArcadeSHMUPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AArcadeSHMUPGameMode();

	// Initialize game save, get all the needed info and load all needed files
	virtual void BeginPlay() override;

	// Called on SpawnPoint's begin play, asking to add itself onto the SpawnPoints array
	void AddSpawnPoint(class ASpawnPoint* SpawnPointToAdd);

	// Calling when the game starts, initiates all the needed save game information and spawns the player
	UFUNCTION(BlueprintCallable, Category = "Gameflow")
		void StartNewGameCycle(FString SaveFileName);

	// Called when the player has died. Saves his score.
	UFUNCTION(BlueprintCallable, Category = "Gameflow")
	void EndGameCycle();

	// Get the score of the current save file
	UFUNCTION(BlueprintPure, Category = "GameSave")
	int GetGameCurrentScore();

	// Get the name of the current save file
	UFUNCTION(BlueprintPure, Category = "GameSave")
		FString GetGameCurrentName();

	// Get the array of names
	UFUNCTION(BlueprintPure, Category = "GameSave")
	TArray<FString> GetNamesArray();

	// Get the array of scores
	UFUNCTION(BlueprintPure, Category = "GameSave")
	TArray<int32> GetScoresArray();

	//Get if we have anything in our game save or not
	UFUNCTION(BlueprintPure, Category = "GameSave")
	bool IsSaveDataNotEmpty();

	// Reacting when enemy broadcasts that it had died
	UFUNCTION()
	void ReactToEnemyDeath(int PointsAwarded, FVector DeathLocation, int WeaponDropPriority, int ModificationDropPriority);
private:
	// Saves a game to save slot 0
	void SaveGame();

	// Loads a game from a slot 0
	void LoadGameSave();

	// Spawn points that are to be used to spawn new enemies
	TArray<class ASpawnPoint*> SpawnPoints;

	// Drop Manager for Drop spawning
	class ADropManager* DropManager;

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

	// Variables to calculate chances of dropping modification/weapon
	int SimpleEnemyWeaponDropChance = 2;
	int AverageEnemyWeaponDropChance = 10;
	int AdvancedEnemyWeaponDropChance = 20;

	// Intencity level that decides the amounts of spawns and their types
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

	// Score system game save reference
	class UScoreSystemSaveGame* GameSave;

	// Array of enemies that are spawned on the field
	TArray<class AEnemy*> EnemiesOnField;

	// Player class to spawn when we start playing
	TSubclassOf<class AArcadeSHMUPPawn> Player;

	// Score of a current session
	int32 CurrentScore = 0;

	// Name of a current sesion
	FString CurrentName = "";

};



