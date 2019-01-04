// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "BallEnemyAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyBallPawn.h"


ABallEnemyAI::ABallEnemyAI()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComp"));

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
}

void ABallEnemyAI::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	// Casting our possessed pawn to the proper enemy class
	Pawn = Cast<AEnemyBallPawn>(InPawn);

	// Initializing blackboard and setting enemy key id. Starting behavior tree
	if (Pawn && Pawn->BehaviorTree)
	{
		BlackboardComp->InitializeBlackboard(*Pawn->BehaviorTree->BlackboardAsset);

		EnemyKeyID = BlackboardComp->GetKeyID("Target");

		BehaviorComp->StartTree(*Pawn->BehaviorTree);
	}
}

FVector ABallEnemyAI::GetOwnerPosition()
{
	// Getting owner location
	return Pawn->GetActorLocation();
}

void ABallEnemyAI::SetOwnerMovePoint(FVector MoveTo)
{
	// Moving to a point
	Pawn->SetPointDestination(MoveTo);
	Pawn->bIsMovingToPoint = true;
}

void ABallEnemyAI::ResetOwnerMovePoint()
{
	// Reseting the value that says that we are moving
	Pawn->bIsMovingToPoint = false;
}

void ABallEnemyAI::StartAttackSequence(FVector Direction)
{
	// Telling enemy to attack the player
	Pawn->StartAttackAt(Direction);
}

