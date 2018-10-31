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

	Pawn = Cast<AEnemyBallPawn>(InPawn);

	if (Pawn && Pawn->BehaviorTree)
	{
		BlackboardComp->InitializeBlackboard(*Pawn->BehaviorTree->BlackboardAsset);

		EnemyKeyID = BlackboardComp->GetKeyID("Target");

		BehaviorComp->StartTree(*Pawn->BehaviorTree);
	}
}

FVector ABallEnemyAI::GetOwnerPosition()
{
	return Pawn->GetActorLocation();
}

void ABallEnemyAI::SetOwnerMovePoint(FVector MoveTo)
{
	Pawn->SetPointDestination(MoveTo);
	Pawn->bIsMovingToPoint = true;
}

void ABallEnemyAI::ResetOwnerMovePoint()
{
	Pawn->bIsMovingToPoint = false;
}

void ABallEnemyAI::StartAttackSequence(FVector Direction)
{
	Pawn->StartAttackAt(Direction);
}

