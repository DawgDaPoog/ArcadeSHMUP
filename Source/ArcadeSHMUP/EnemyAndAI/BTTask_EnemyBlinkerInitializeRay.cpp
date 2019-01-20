// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_EnemyBlinkerInitializeRay.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyBlinkerAI.h"

EBTNodeResult::Type UBTTask_EnemyBlinkerInitializeRay::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyBlinkerAI* EnemyAI = Cast<AEnemyBlinkerAI>(OwnerComp.GetAIOwner());
	APawn* Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAI->EnemyKeyID));

	if (Player)
	{
		EnemyAI->InitializeRayTo(Player->GetActorLocation());
	}
	else
	{
		EnemyAI->InitializeRayTo(FVector(0.f, 0.f, 260.f));
	}
	return EBTNodeResult::Succeeded;
}
