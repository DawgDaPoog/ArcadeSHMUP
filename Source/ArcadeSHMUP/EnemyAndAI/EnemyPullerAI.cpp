// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPullerAI.h"
#include "EnemyPuller.h"
#include "GameFramework/Pawn.h"

void AEnemyPullerAI::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	EnemyClassPawn = Cast<AEnemyPuller>(InPawn);
}

void AEnemyPullerAI::PullPlayer(APawn* Player, float ForceModificator)
{
	EnemyClassPawn->PullTowardsSelf(Player, ForceModificator);
}
