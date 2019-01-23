// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_EnemyPullerPull.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API UBTTask_EnemyPullerPull : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = "Pull")
		float PullEffectRange = 400.f;
		
		UPROPERTY(EditAnywhere, Category = "Pull")
		float PullForceModificator = 1.f;

		EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory);
};
