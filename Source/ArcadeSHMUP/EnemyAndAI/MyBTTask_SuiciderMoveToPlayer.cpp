// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "MyBTTask_SuiciderMoveToPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemySuiciderAI.h"

EBTNodeResult::Type UMyBTTask_SuiciderMoveToPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemySuiciderAI* EnemyAI = Cast<AEnemySuiciderAI>(OwnerComp.GetAIOwner());

	if (!EnemyAI)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAI->TargetKeyID));
	if (Player)
	{
		FVector Direction = Player->GetActorLocation() - EnemyAI->GetOwnerPosition();

		EnemyAI->SetPerTickVectorValueTowards(Direction);
	}

	return EBTNodeResult::Succeeded;
}
