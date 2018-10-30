// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "BTTask_MoveToSpot.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BallEnemyAI.h"

EBTNodeResult::Type UBTTask_MoveToSpot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABallEnemyAI* EnemyAI = Cast<ABallEnemyAI>(OwnerComp.GetAIOwner());

	APawn* Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAI->EnemyKeyID));
	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("We got a task telling me to move towards %s"), *Player->GetName());
		return EBTNodeResult::Succeeded;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Task failed, didn't get the player"));
		return EBTNodeResult::Failed;
	}
}


