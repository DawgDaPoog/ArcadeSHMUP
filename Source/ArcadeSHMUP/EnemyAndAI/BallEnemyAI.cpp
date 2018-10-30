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

	AEnemyBallPawn* Pawn = Cast<AEnemyBallPawn>(InPawn);

	if (Pawn && Pawn->BehaviorTree)
	{
		BlackboardComp->InitializeBlackboard(*Pawn->BehaviorTree->BlackboardAsset);

		EnemyKeyID = BlackboardComp->GetKeyID("Target");

		BehaviorComp->StartTree(*Pawn->BehaviorTree);
	}
}
