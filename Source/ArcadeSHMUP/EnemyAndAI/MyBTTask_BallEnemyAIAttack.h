// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_BallEnemyAIAttack.generated.h"

/**
 *  A task that only works for BallEnemy. Tells it to attack at the location of a player.
 */
UCLASS()
class ARCADESHMUP_API UMyBTTask_BallEnemyAIAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
