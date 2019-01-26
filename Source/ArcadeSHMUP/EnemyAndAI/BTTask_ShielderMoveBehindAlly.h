// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ShielderMoveBehindAlly.generated.h"

/**
 * Node that works for EnemyShielder. Tells it to move behind currently bond with enemy, taking cover from player fire.
 */
UCLASS()
class ARCADESHMUP_API UBTTask_ShielderMoveBehindAlly : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
