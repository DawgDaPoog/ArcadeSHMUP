// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "EnemySuiciderAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemySuicider.h"

AEnemySuiciderAI::AEnemySuiciderAI()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComp"));

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
}

void AEnemySuiciderAI::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	Pawn = Cast<AEnemySuicider>(InPawn);

	if (Pawn && Pawn->BehaviorTree)
	{
		BlackboardComp->InitializeBlackboard(*Pawn->BehaviorTree->BlackboardAsset);

		EnemyKeyID = BlackboardComp->GetKeyID("Target");

		BehaviorComp->StartTree(*Pawn->BehaviorTree);
	}
}

void AEnemySuiciderAI::SetPerTickVectorValueTowards(FVector PlayerLocation)
{
	Pawn->SetForceVectorTo(PlayerLocation);
}

FVector AEnemySuiciderAI::GetOwnerPosition()
{
	return Pawn->GetActorLocation();
}


