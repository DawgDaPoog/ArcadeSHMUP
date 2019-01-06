// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "BTTask_ShooterEnemyRandomMove.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyShooterAI.h"

EBTNodeResult::Type UBTTask_ShooterEnemyRandomMove::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyShooterAI* EnemyAI = Cast<AEnemyShooterAI>(OwnerComp.GetAIOwner());

	if (!EnemyAI)
	{
		return EBTNodeResult::Failed;
	}

	// Find a random vector in a very long range
	FVector RandVector = FMath::VRand();

	RandVector.Z = 260.f;
	RandVector *= 10000.f;
	RandVector.Z = 260.f;

	EnemyAI->SetForceTo(RandVector);

	return EBTNodeResult::Succeeded;
}
