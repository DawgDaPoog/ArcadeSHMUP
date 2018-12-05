// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ArcadeSHMUPGameMode.h"
#include "ArcadeSHMUPPawn.h"
#include "EnemyAndAI/SpawnPoint.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAndAI/Enemy.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"
#include "ConstructorHelpers.h"
#include "ArcadeSHMUPPawn.h"
#include "GameFramework/PlayerController.h"

AArcadeSHMUPGameMode::AArcadeSHMUPGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = NULL;

	static ConstructorHelpers::FClassFinder<AArcadeSHMUPPawn> PlayerFinder(TEXT("/Game/PlayerAndPlayerLogic/BP_ArcadeSHMUPPawn"));

	if (PlayerFinder.Succeeded())
	{
		Player = PlayerFinder.Class;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Gameplay couldn't find Player Class!"));
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

	GameSave = Cast<UScoreSystemSaveGame>(UGameplayStatics::CreateSaveGameObject(UScoreSystemSaveGame::StaticClass()));
	if (UGameplayStatics::DoesSaveGameExist(TEXT("0"), 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded Game"))
		GameSave = Cast<UScoreSystemSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("0"), 0));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Saved New Game"))
		UGameplayStatics::SaveGameToSlot(GameSave, TEXT("0"), 0);
		GameSave = Cast<UScoreSystemSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("0"), 0));
	}

	//Set a wave spawn timer
	GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &AArcadeSHMUPGameMode::WaveSpawn, 5.f, true, 5.f);
}

void AArcadeSHMUPGameMode::AddSpawnPoint(ASpawnPoint * SpawnPointToAdd)
{
	// Adding a spawn point to the array
	SpawnPoints.Add(SpawnPointToAdd);
}

void AArcadeSHMUPGameMode::StartNewGameCycle(FString SaveFileName)
{
	FNameToScore NewNameScore;
	NewNameScore.Score = 0;
	NewNameScore.Name = SaveFileName;

	CurrentName = SaveFileName;

	// Adding new ScoreName to the game save
	if (GameSave)
	{
		UE_LOG(LogTemp, Warning, TEXT("Added new NameScore"))
		GameSave->NamesAndScores.Add(NewNameScore);
	}

	for (auto NameScores : GameSave->NamesAndScores)
	{
		UE_LOG(LogTemp, Warning, TEXT("Name %s"), *NameScores.Name);
			UE_LOG(LogTemp, Warning, TEXT("Score Amount %i"), NameScores.Score);
	}

	//Finding the player start
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);


	if (FoundActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Player Start In the game was found"));
		return;
	}

	APlayerStart* PlayerStart = Cast<APlayerStart>(FoundActors.Last());
	UE_LOG(LogTemp, Warning, TEXT("Setting Player Start"));
	// Spawning the player at player start
	if (PlayerStart)
	{
		auto PlayerActor = GetWorld()->SpawnActor<AArcadeSHMUPPawn>(Player, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation());

		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Player Start"));
	}
}

void AArcadeSHMUPGameMode::EndGameCycle()
{
	GameSave->NamesAndScores.Last().Name = CurrentName;
	GameSave->NamesAndScores.Last().Score = CurrentScore;
	if (GameSave)
	{
		UE_LOG(LogTemp,Warning,TEXT("Saved Game"))
		UGameplayStatics::SaveGameToSlot(GameSave, TEXT("0"), 0);
		GameSave = Cast<UScoreSystemSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("0"), 0));
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
		UE_LOG(LogTemp, Warning, TEXT("Save Data Is Not Empty"))
		return true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Saved Data Is EMpty"))
	return false;
}


void AArcadeSHMUPGameMode::ReactToEnemyDeath(int PointsAwarded)
{
	// Increrase the score of the player by the cost of the enemy that died
	CurrentScore += PointsAwarded;
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
