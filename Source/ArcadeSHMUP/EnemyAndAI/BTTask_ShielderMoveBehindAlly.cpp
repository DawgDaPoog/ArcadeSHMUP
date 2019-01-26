// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_ShielderMoveBehindAlly.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyShielderAI.h"

EBTNodeResult::Type UBTTask_ShielderMoveBehindAlly::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyShielderAI* EnemyAI = Cast<AEnemyShielderAI>(OwnerComp.GetAIOwner());

	if (!EnemyAI)
	{
		EBTNodeResult::Failed;
	}

	APawn* Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAI->TargetKeyID));
	if (!Player)
	{
		return EBTNodeResult::Succeeded;
	}

	APawn* Ally = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAI->TopAllyKeyID));
	if (!Ally)
	{
		return EBTNodeResult::Succeeded;
	}

	if (Player && Ally)
	{
		// If we are less than 250 units away, stand
		float ShielderToAllyRange = EnemyAI->GetPawn()->GetDistanceTo(Ally);
		if (ShielderToAllyRange < 300.f)
		{
			EnemyAI->SetPerTickVectorValueTowards(EnemyAI->GetOwnerPosition());
			return EBTNodeResult::Succeeded;
		}

		// Find vector from Player to Ally
		FVector PlayerToAllyVector = Ally->GetActorLocation() - Player->GetActorLocation();
		FVector PlayerToAllyVectorNormal = PlayerToAllyVector.GetSafeNormal();

		// Find where is 100 units behind our ally
		FVector Direction = Ally->GetActorLocation() + PlayerToAllyVectorNormal*350.f - EnemyAI->GetOwnerPosition();

		// Set force towards our destination
		EnemyAI->SetPerTickVectorValueTowards(Direction);
	}

	return EBTNodeResult::Succeeded;
}
