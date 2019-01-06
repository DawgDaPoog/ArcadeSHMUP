// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "MyBTTask_BallEnemyAIAttack.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BallEnemyAI.h"

EBTNodeResult::Type UMyBTTask_BallEnemyAIAttack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ABallEnemyAI* EnemyAI = Cast<ABallEnemyAI>(OwnerComp.GetAIOwner());

	if (!EnemyAI)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAI->EnemyKeyID));
	if (Player)
	{
		FVector DirectionVector = Player->GetActorLocation() - EnemyAI->GetOwnerPosition();
		FVector Direction = DirectionVector.GetSafeNormal();

		EnemyAI->StartAttackSequence(Direction);
	}

	return EBTNodeResult::Succeeded;
}
