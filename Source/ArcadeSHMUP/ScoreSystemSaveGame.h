// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ScoreSystemSaveGame.generated.h"

// Struct that relates Name of the save file/player to it's score
USTRUCT(BlueprintType)
struct FNameToScore
{
	GENERATED_BODY()

	// Name of the player
	UPROPERTY(BlueprintReadOnly)
	FString Name;

	// Player's score
	UPROPERTY(BlueprintReadOnly)
	int32 Score;

	int32 GetScore() { return Score; }

	FString GetName() { return Name; }

	// Overloading < operator so that we can properely sort array of this struct. Sorting from the highest to the smallest
	FORCEINLINE bool operator<(const FNameToScore &Other) const
	{
		return Score > Other.Score;
	}
};

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API UScoreSystemSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	// Array of Name to Score relations to save in the save file
	UPROPERTY(VisibleAnywhere, Category = NamesAndScores)
	TArray<FNameToScore> NamesAndScores;

	void SortScores();
};
