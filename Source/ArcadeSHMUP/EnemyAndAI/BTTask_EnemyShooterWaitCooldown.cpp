// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "BTTask_EnemyShooterWaitCooldown.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "EnemyShooterAI.h"

EBTNodeResult::Type UBTTask_EnemyShooterWaitCooldown::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	bNotifyTick = true;
	bTimerDone = false;

	AEnemyShooterAI* EnemyAI = Cast<AEnemyShooterAI>(OwnerComp.GetAIOwner());

	if (!EnemyAI)
	{
		return EBTNodeResult::Failed;
	}

	FTimerHandle TimerHandle;

	FTimerDelegate TimerDelegate;

	TimerDelegate.BindLambda([this]()
	{
		bTimerDone = true;
	});

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, EnemyAI->GetShootingDelay(), false);

	return EBTNodeResult::InProgress;
}

void UBTTask_EnemyShooterWaitCooldown::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	if (bTimerDone)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
