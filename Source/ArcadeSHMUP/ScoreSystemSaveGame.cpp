// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "ScoreSystemSaveGame.h"

void UScoreSystemSaveGame::SortScores()
{
	if (NamesAndScores.Num() != 0)
	{
		// Sorting the array
		NamesAndScores.Sort();
	}
}
