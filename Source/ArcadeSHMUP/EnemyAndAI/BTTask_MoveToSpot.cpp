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
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoveToSpot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//APawn* Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAI->EnemyKeyID));
	ABallEnemyAI* EnemyAI = Cast<ABallEnemyAI>(OwnerComp.GetAIOwner());

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


	FVector CurrentPosition = EnemyAI->GetOwnerPosition();
	RandomVectorCloseBy = CurrentPosition;
	float MinRange = 400.f;
	float MaxRange = 700.f;

	while (FVector::Dist(RandomVectorCloseBy, CurrentPosition) < MinRange)
	{
		RandomVectorCloseBy = FVector(FMath::RandRange(CurrentPosition.X - MaxRange, CurrentPosition.X + MaxRange), FMath::RandRange(CurrentPosition.Y - MaxRange, CurrentPosition.Y + MaxRange), CurrentPosition.Z);
	}
	
	EnemyAI->SetOwnerMovePoint(RandomVectorCloseBy);

	return EBTNodeResult::InProgress;
}

void UBTTask_MoveToSpot::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	ABallEnemyAI* EnemyAI = Cast<ABallEnemyAI>(OwnerComp.GetAIOwner());
	FVector CurrentPosition = EnemyAI->GetOwnerPosition();

	if (CurrentPosition.Equals(RandomVectorCloseBy, 50.f))
	{
		EnemyAI->ResetOwnerMovePoint();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}


