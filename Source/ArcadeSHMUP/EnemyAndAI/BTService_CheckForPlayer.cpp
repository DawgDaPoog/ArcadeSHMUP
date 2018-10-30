// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "BTService_CheckForPlayer.h"
#include "BallEnemyAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Engine/World.h"
#include "BehaviorTree/BTNode.h"

UBTService_CheckForPlayer::UBTService_CheckForPlayer()
{
	bCreateNodeInstance = true;
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	ABallEnemyAI* EnemyAI = Cast<ABallEnemyAI>(OwnerComp.GetAIOwner());

	if (EnemyAI)
	{
		APawn* Enemy = GetWorld()->GetFirstPlayerController()->GetPawn();

		if (Enemy)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyAI->EnemyKeyID, Enemy);
			
		}
	}
}

