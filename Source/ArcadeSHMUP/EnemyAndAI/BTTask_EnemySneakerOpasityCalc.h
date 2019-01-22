// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_EnemySneakerOpasityCalc.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API UBTTask_EnemySneakerOpasityCalc : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(Category = VisibilityRange, EditAnywhere)
	float VisibilityRangeBarrier = 200.f;

	UPROPERTY(Category = VisibilityRange, EditAnywhere)
	float FullVisibilityRange = 50.f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
