// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_EnemyShooterWaitCooldown.generated.h"

struct FBTWaitTaskMemory
{
	/** time left */
	float RemainingWaitTime;
};

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API UBTTask_EnemyShooterWaitCooldown : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTask_EnemyShooterWaitCooldown();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual uint16 GetInstanceMemorySize() const override;

	virtual void DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const override;

	bool bTimerDone = false;

	float WaitTimeSeconds;
};
