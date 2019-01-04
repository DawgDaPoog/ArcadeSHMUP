// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "BallEnemyAI.h"
#include "EnemyBallPawn.h"



void ABallEnemyAI::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	EnemyClassPawn = Cast<AEnemyBallPawn>(InPawn);
}

void ABallEnemyAI::SetOwnerMovePoint(FVector MoveTo)
{
	// Moving to a point
	EnemyClassPawn->SetPointDestination(MoveTo);
	EnemyClassPawn->bIsMovingToPoint = true;
}

void ABallEnemyAI::ResetOwnerMovePoint()
{
	// Reseting the value that says that we are moving
	EnemyClassPawn->bIsMovingToPoint = false;
}

void ABallEnemyAI::StartAttackSequence(FVector Direction)
{
	// Telling enemy to attack the player
	EnemyClassPawn->StartAttackAt(Direction);
}

