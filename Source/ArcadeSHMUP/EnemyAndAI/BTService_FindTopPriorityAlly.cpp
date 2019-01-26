// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_FindTopPriorityAlly.h"
#include "EnemyShielderAI.h"
#include "Enemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BTNode.h"

UBTService_FindTopPriorityAlly::UBTService_FindTopPriorityAlly()
{
	bCreateNodeInstance = true;
}

void UBTService_FindTopPriorityAlly::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	// Getting the enemy ai
	AEnemyShielderAI* EnemyAI = Cast<AEnemyShielderAI>(OwnerComp.GetAIOwner());

	// Early return if we didn't get our driving AI
	if (!EnemyAI)
	{
		return;
	}

	// Getting the current target
	auto CurrentTarget = Cast<AEnemy>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAI->TopAllyKeyID));

	// Array to help find actors in level 
	TArray<AActor*> FoundActors;

	// Find all the enemies on map
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundActors);

	// Variables to assist the finding of a candidate
	int HighestPriorityFound = 0;
	AEnemy* CandidateForTarget = nullptr;

	// Cycling through all the found enemies and making the first one with the highest priority a candidate for a target
	for (auto Enemy : FoundActors)
	{
		AEnemy* CurrentEnemy = Cast<AEnemy>(Enemy);
		if (CurrentEnemy->GetWeaponDropPriority() > HighestPriorityFound && CurrentEnemy->GetWeaponDropPriority() <= 3)
		{
			// If we found another shielder, skip
			AEnemyShielder* ShielderCheck = Cast<AEnemyShielder>(CurrentEnemy);
			if (ShielderCheck)
			{
				continue;
			}
			CandidateForTarget = CurrentEnemy;
		}
	}

	// if we didn't find any candidates, bail out
	if (CandidateForTarget)
	{
		if (EnemyAI)
		{
			// If we have currently set target, compare it's priority with a candidate
			if (CurrentTarget)
			{
				// If our candidate has higher priority, set him as a blackboard value
				if (CandidateForTarget->GetWeaponDropPriority() > CurrentTarget->GetWeaponDropPriority())
				{
					OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyAI->TopAllyKeyID, CandidateForTarget);
				}
			}
			else
			{
				// Set candidate as a blackboard target if we have no target yet
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyAI->TopAllyKeyID, CandidateForTarget);
			}
		}
	}
}
