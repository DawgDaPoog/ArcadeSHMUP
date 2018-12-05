// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ArcadeSHMUPGameMode.h"
#include "ArcadeSHMUPPawn.h"
#include "EnemyAndAI/SpawnPoint.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAndAI/Enemy.h"
#include "EnemyAndAI/SpawnerActor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "ConstructorHelpers.h"
#include "ArcadeSHMUPPawn.h"
#include "GameFramework/PlayerController.h"
#include "Drops/DropManager.h"

AArcadeSHMUPGameMode::AArcadeSHMUPGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = NULL;

	static ConstructorHelpers::FClassFinder<AArcadeSHMUPPawn> PlayerFinder(TEXT("/Game/PlayerAndPlayerLogic/BP_ArcadeSHMUPPawn"));

	if (PlayerFinder.Succeeded())
	{
		Player = PlayerFinder.Class;
	}

	// Default values for spawn frequency and wave intencity
	SpawnFrequency = 5.f;
	Intencity = 1;

	// Default setup for first wave of enemy spawning
	WaveSpawnSimpleMin = 2;
	WaveSpawnSimpleMax = 4;

	WaveSpawnAverageMin = 0;
	WaveSpawnAverageMax = 0;

	WaveSpawnAdvancedMin = 0;
	WaveSpawnAdvancedMax = 0;
}

void AArcadeSHMUPGameMode::BeginPlay()
{
	Super::BeginPlay();
	// Create or Load a save file

	// Create GameSave variable
	GameSave = Cast<UScoreSystemSaveGame>(UGameplayStatics::CreateSaveGameObject(UScoreSystemSaveGame::StaticClass()));

	// Check if game save already exists
	if (UGameplayStatics::DoesSaveGameExist(TEXT("0"), 0))
	{
		// Load GameSave
		LoadGameSave();
	}
	else
	{
		// Create New Game Save
		SaveGame();
		LoadGameSave();
	}

	// Finding Drop Manager in the level
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADropManager::StaticClass(), FoundActors);

	// Setting our DropManager to the last found 
	DropManager = Cast<ADropManager>(FoundActors.Last());
	check(DropManager);

	// Sort scores in the save file
	GameSave->SortScores();

	//Set a wave spawn timer
	GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &AArcadeSHMUPGameMode::WaveSpawn, 5.f, true, 5.f);
}

void AArcadeSHMUPGameMode::SaveGame()
{
	UGameplayStatics::SaveGameToSlot(GameSave, TEXT("0"), 0);
}

void AArcadeSHMUPGameMode::LoadGameSave()
{
	GameSave = Cast<UScoreSystemSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("0"), 0));
}

void AArcadeSHMUPGameMode::AddSpawnPoint(ASpawnPoint * SpawnPointToAdd)
{
	// Adding a spawn point to the array
	SpawnPoints.Add(SpawnPointToAdd);
}

void AArcadeSHMUPGameMode::StartNewGameCycle(FString SaveFileName)
{
	// Reseting the score and setting new name
	CurrentScore = 0;
	CurrentName = SaveFileName;

	// Array to help find actors in level 
	TArray<AActor*> FoundActors;

	// Finding All Enemies in level
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundActors);

	// Destroying Every Single one of Enemies
	for (auto Enemy : FoundActors)
	{
		Enemy->Destroy();
	}

	// Find all the lingering SpawnerActor's
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnerActor::StaticClass(), FoundActors);

	// Destroying them
	for (auto SpawnerActor : FoundActors)
	{
		SpawnerActor->Destroy();
	}

	//Finding the player start
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	APlayerStart* PlayerStart = Cast<APlayerStart>(FoundActors.Last());

	// Spawning the player at player start
	check(PlayerStart)
	auto PlayerActor = GetWorld()->SpawnActor<AArcadeSHMUPPawn>(Player, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation());
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	
	
}

void AArcadeSHMUPGameMode::EndGameCycle()
{
	// Creating new FNameToScore struct to then push in the save file
	FNameToScore NewNameScore;
	NewNameScore.Score = CurrentScore;
	NewNameScore.Name = CurrentName;

	// Load Game Save
	LoadGameSave();

	if (GameSave)
	{
		// Adding new ScoreName to the game save and sorting
		GameSave->NamesAndScores.Add(NewNameScore);
		GameSave->SortScores();
		
		// Reload Game Save
		SaveGame();
		LoadGameSave();
	}
}

int AArcadeSHMUPGameMode::GetGameCurrentScore()
{
	return CurrentScore;
}

FString AArcadeSHMUPGameMode::GetGameCurrentName()
{
	return CurrentName;
}

TArray<FString> AArcadeSHMUPGameMode::GetNamesArray()
{
	if (GameSave->NamesAndScores.Num() != 0)
	{
		TArray<FString> retVal;
		for (auto NameScore : GameSave->NamesAndScores)
		{
			retVal.Add(NameScore.Name);
		}
		return retVal;
	}
	return TArray<FString>();
}

TArray<int32> AArcadeSHMUPGameMode::GetScoresArray()
{
	if (GameSave->NamesAndScores.Num() != 0)
	{
		TArray<int32> retVal;
		for (auto NameScore : GameSave->NamesAndScores)
		{
			retVal.Add(NameScore.Score);
		}
		return retVal;
	}
	return TArray<int32>();
}

bool AArcadeSHMUPGameMode::IsSaveDataNotEmpty()
{
	if (GameSave->NamesAndScores.Num() != 0)
	{
		return true;
	}
	return false;
}


void AArcadeSHMUPGameMode::ReactToEnemyDeath(int PointsAwarded, FVector DeathLocation, int WeaponDropPriority, int ModificationDropPriority)
{
	// Increrase the score of the player by the cost of the enemy that died
	CurrentScore += PointsAwarded;

	// Chance to drop a weapon on it's death location, depenging on the type of an enemy
	int TempDropChance = 0; 
	switch (WeaponDropPriority)
	{
	case 0:
		break;
	case 1:
		TempDropChance = SimpleEnemyWeaponDropChance;
		break;
	case 2:
		TempDropChance = AverageEnemyWeaponDropChance;
		break;
	case 3:
		TempDropChance = AdvancedEnemyWeaponDropChance;
		break;
	case 4:
		TempDropChance = 100;
	}

	if (FMath::RandRange(1, 100) <= TempDropChance)
	{
		DropManager->InitializeRandomDropAtLocation(DeathLocation);
	}
	// Chance to drop modification on it's death location, depending on the type of an enemy
}

void AArcadeSHMUPGameMode::WaveSpawn()
{
	// Early return if we have no spawn points
	if (SpawnPoints.Num() == 0) return;

	// Spawning all enemy types	
	SpawnWaveType(1);
	SpawnWaveType(2);
	SpawnWaveType(3);

	// Increasing Intensity Level

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
