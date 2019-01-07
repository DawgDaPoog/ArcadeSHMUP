// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "BTTask_EnemyShooterWaitCooldown.h"
#include "EnemyShooterAI.h"


UBTTask_EnemyShooterWaitCooldown::UBTTask_EnemyShooterWaitCooldown()
{
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTask_EnemyShooterWaitCooldown::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	bTimerDone = false;

	AEnemyShooterAI* EnemyAI = Cast<AEnemyShooterAI>(OwnerComp.GetAIOwner());

	
	if (!EnemyAI)
	{
		return EBTNodeResult::Failed;
	}

	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime = EnemyAI->GetShootingDelay();

	return EBTNodeResult::InProgress;
}

void UBTTask_EnemyShooterWaitCooldown::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	MyMemory->RemainingWaitTime -= DeltaSeconds;

	if (MyMemory->RemainingWaitTime <= 0.f)
	{
		// continue execution from this node
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

uint16 UBTTask_EnemyShooterWaitCooldown::GetInstanceMemorySize() const
{
	return sizeof(FBTWaitTaskMemory);
}

void UBTTask_EnemyShooterWaitCooldown::DescribeRuntimeValues(const UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);

	FBTWaitTaskMemory* MyMemory = (FBTWaitTaskMemory*)NodeMemory;
	if (MyMemory->RemainingWaitTime)
	{
		Values.Add(FString::Printf(TEXT("remaining: %ss"), *FString::SanitizeFloat(MyMemory->RemainingWaitTime)));
	}
}


