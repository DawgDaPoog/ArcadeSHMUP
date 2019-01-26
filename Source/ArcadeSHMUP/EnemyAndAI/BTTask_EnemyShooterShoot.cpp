// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "BTTask_EnemyShooterShoot.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyShooterAI.h"

EBTNodeResult::Type UBTTask_EnemyShooterShoot::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyShooterAI* EnemyAI = Cast<AEnemyShooterAI>(OwnerComp.GetAIOwner());

	if (!EnemyAI)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAI->TargetKeyID));
	if (Player)
	{
		EnemyAI->CallShootAt(Player->GetActorLocation());
	}

	return EBTNodeResult::Succeeded;
}
