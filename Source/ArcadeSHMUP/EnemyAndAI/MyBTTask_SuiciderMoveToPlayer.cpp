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
	APawn* Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAI->EnemyKeyID));
	if (Player)
	{
		FVector DirectionVector = Player->GetActorLocation() - EnemyAI->GetOwnerPosition();
		FVector Direction = DirectionVector;

		EnemyAI->SetPerTickVectorValueTowards(Direction);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Player not found"));
	}

	return EBTNodeResult::Succeeded;
}
