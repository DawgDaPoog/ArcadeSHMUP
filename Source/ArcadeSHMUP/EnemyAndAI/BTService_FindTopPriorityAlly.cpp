// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_FindTopPriorityAlly.h"
#include "EnemyAIBase.h"
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
	AEnemyAIBase* EnemyAI = Cast<AEnemyAIBase>(OwnerComp.GetAIOwner());

	// Getting player (Enemy for this ai)
	// Array to help find actors in level 
	TArray<AActor*> FoundActors;

	// Find all lingering drops in the area
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundActors);

	//// Destroy all lingering drops
	//for (auto Enemy : FoundActors)
	//{
	//	if (Drop)
	//	{
	//		Drop->Destroy();
	//	}
	//}

	//if (EnemyAI)
	//{
	//	if (Enemy)
	//	{
	//		// Setting the player as the enemy for our AI
	//		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyAI->TargetKeyID, Enemy);
	//	}
	//}
}
