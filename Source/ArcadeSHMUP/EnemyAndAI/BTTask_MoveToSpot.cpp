// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "BTTask_MoveToSpot.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "BallEnemyAI.h"

UBTTask_MoveToSpot::UBTTask_MoveToSpot(const FObjectInitializer& objectInitializer)
{
	// Setting tick to true to check if we reached the intended place yet
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoveToSpot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Getting enemy ai
	ABallEnemyAI* EnemyAI = Cast<ABallEnemyAI>(OwnerComp.GetAIOwner());

	// Setting the break handle if we take too long to get to the intended place
	FTimerHandle BreakHandle;
	GetWorld()->GetTimerManager().SetTimer(
		BreakHandle, 
		[this,&OwnerComp,EnemyAI]()
		{
			EnemyAI->ResetOwnerMovePoint();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}, 
		1.5f, 
		false
		);

	// Finding the current position and a random position close by
	FVector CurrentPosition = EnemyAI->GetOwnerPosition();
	RandomVectorCloseBy = CurrentPosition;
	float MinRange = 400.f;
	float MaxRange = 700.f;

	// Generating a random position close to the current one in the given ranges
	while (FVector::Dist(RandomVectorCloseBy, CurrentPosition) < MinRange)
	{
		RandomVectorCloseBy = FVector(FMath::RandRange(CurrentPosition.X - MaxRange, CurrentPosition.X + MaxRange), FMath::RandRange(CurrentPosition.Y - MaxRange, CurrentPosition.Y + MaxRange), CurrentPosition.Z);
	}
	
	// Telling the ai to set the movement point
	EnemyAI->SetOwnerMovePoint(RandomVectorCloseBy);

	// Returning the node in progress
	return EBTNodeResult::InProgress;
}

void UBTTask_MoveToSpot::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	// Getting the Ai
	ABallEnemyAI* EnemyAI = Cast<ABallEnemyAI>(OwnerComp.GetAIOwner());

	// Finding the current position
	FVector CurrentPosition = EnemyAI->GetOwnerPosition();

	// If our current position equals the point we were traveling to, return node succeeded
	if (CurrentPosition.Equals(RandomVectorCloseBy, 50.f))
	{
		EnemyAI->ResetOwnerMovePoint();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}


