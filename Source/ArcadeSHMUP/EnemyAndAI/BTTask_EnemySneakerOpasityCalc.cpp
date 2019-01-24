// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_EnemySneakerOpasityCalc.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemySneakerAI.h"

EBTNodeResult::Type UBTTask_EnemySneakerOpasityCalc::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemySneakerAI* EnemyAI = Cast<AEnemySneakerAI>(OwnerComp.GetAIOwner());

	if (!EnemyAI)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAI->TargetKeyID));
	if (Player)
	{
		FVector DirectionVector = Player->GetActorLocation() - EnemyAI->GetOwnerPosition();
		
		if (DirectionVector.Size() <= FullVisibilityRange)
		{
			EnemyAI->SetShipsOpacityTo(1.f);
		}
		else if (DirectionVector.Size() <= VisibilityRangeBarrier)
		{
			EnemyAI->SetShipsOpacityTo((VisibilityRangeBarrier - DirectionVector.Size())/VisibilityRangeBarrier);
		}
		else
		{
			EnemyAI->SetShipsOpacityTo(0.f);
		}
	}
	else
	{
		EnemyAI->SetShipsOpacityTo(1.f);
	}

	return EBTNodeResult::Succeeded;
}
