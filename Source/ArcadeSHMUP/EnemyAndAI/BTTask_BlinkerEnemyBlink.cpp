// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_BlinkerEnemyBlink.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyBlinkerAI.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

EBTNodeResult::Type UBTTask_BlinkerEnemyBlink::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AEnemyBlinkerAI* EnemyAI = Cast<AEnemyBlinkerAI>(OwnerComp.GetAIOwner());
	APawn* Player = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAI->EnemyKeyID));

	FVector LocationToSpawnTo;

	// Generate random place to teleport to untill we get a proper one or untill we are out of attempts to find one
	int attempts = 0;
	do
	{
		LocationToSpawnTo = FVector(FMath::RandRange(-850.f, 850.f), FMath::RandRange(-1550.f, 1550.f), 260.f);
		attempts++;
	} while (!CanTeleportToLocation(LocationToSpawnTo) && attempts <= 20);

	// If we couldn't find location to teleport to, bail out
	if (!CanTeleportToLocation(LocationToSpawnTo))
	{
		return EBTNodeResult::Succeeded;
	}

	// If we didn't have a player found, bail out
	//if (!Player)
	//{
	//	return EBTNodeResult::Succeeded;
	//}

	// If we have a proper AI class, tell it ti teleport
	if (EnemyAI)
	{
		// Start cooldown
		EnemyAI->StartBlinkCooldown();

		// Blink
		EnemyAI->InitializeBlinkTo(LocationToSpawnTo);
	}
	return EBTNodeResult::Succeeded;
}

bool UBTTask_BlinkerEnemyBlink::CanTeleportToLocation(FVector Location)
{
	// Casting multisweep to find all the collision in the radius
	TArray<FHitResult> HitResults;
	float Radius = 100.f;
	bool HasHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(Radius)
	);
	
	
	
	// Uncomment next two lines to draw debug lines for clarifying spawn check radii
	//FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	//DrawDebugSphere(GetWorld(), Location, Radius, 20, ResultColor, true, 100);
	
	// Checking for collision with player or enemy
	for (auto HitResult : HitResults)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor->ActorHasTag(FName("Enemy")) || HitActor->ActorHasTag(FName("Player")))
		{
			return false;
		}
	}
	
	return true;
}

