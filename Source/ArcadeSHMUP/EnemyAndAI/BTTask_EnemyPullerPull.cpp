// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_EnemyPullerPull.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyPullerAI.h"
#include "GameFramework/Pawn.h"

EBTNodeResult::Type UBTTask_EnemyPullerPull::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyPullerAI* EnemyAI = Cast<AEnemyPullerAI>(OwnerComp.GetAIOwner());

	if (!EnemyAI)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAI->TargetKeyID));
	if (Player)
	{
		float Range = (EnemyAI->GetOwnerPosition() - Player->GetActorLocation()).Size();

		if (Range <= PullEffectRange)
		{
			float RangeForceModificator = PullForceModificator * ((PullEffectRange - Range) / PullEffectRange);
			EnemyAI->PullPlayer(Player, RangeForceModificator);
		}
	}

	return EBTNodeResult::Succeeded;
}
