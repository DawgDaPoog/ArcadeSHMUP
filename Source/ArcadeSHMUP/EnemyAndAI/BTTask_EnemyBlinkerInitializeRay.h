// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_EnemyBlinkerInitializeRay.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API UBTTask_EnemyBlinkerInitializeRay : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) override;
};
