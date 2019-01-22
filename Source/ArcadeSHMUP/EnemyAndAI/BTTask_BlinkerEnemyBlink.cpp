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

	if (!Player)
	{
		return EBTNodeResult::Succeeded;
	}
	
	FVector LocationToSpawnTo;

	
	if (EnemyAI->GetPossessedPawn())
	{
		FVector EnemyLocation = EnemyAI->GetOwnerPosition();

		// If player and blinker are both on the same side of the field
		if ((Player->GetActorLocation().Y > 0.f && EnemyLocation.Y > 0.f) || (Player->GetActorLocation().Y < 0.f && EnemyLocation.Y < 0.f))
		{
			// Jump diagonally
			if (EnemyLocation.X < 0)
			{
				if (EnemyLocation.Y > 0)
				{
					LocationToSpawnTo = GenerateLocationIn(FVector(0.f, -1550.f, 0.f), FVector(850.f, 0.f, 0.f)); // Top Left
				}
				else
				{
					LocationToSpawnTo = GenerateLocationIn(FVector(0.f), FVector(850.f, 1550.f, 0.f)); // Top Right
				}
			}
			else
			{
				if (EnemyLocation.Y > 0)
				{
					LocationToSpawnTo = GenerateLocationIn(FVector(-850.f, -1550.f, 0.f), FVector(0.f)); // Bottow Left
				}
				else
				{
					LocationToSpawnTo = GenerateLocationIn(FVector(-850.f, 0.f, 0.f), FVector(0.f, 1550.f, 0.f)); // Bottom Right
				}
			}
		}
		else
		{
			// Jump Horrizontally or Vertically
			bool CoinFlip = FMath::RandRange(0, 1);

			if (CoinFlip) // Jump Vertically
			{
				if (EnemyLocation.X < 0)
				{
					if (EnemyLocation.Y > 0)
					{
						LocationToSpawnTo = GenerateLocationIn(FVector(0.f), FVector(850.f, 1550.f, 0.f)); // Top Right
					}
					else
					{
						LocationToSpawnTo = GenerateLocationIn(FVector(0.f, -1550.f, 0.f), FVector(850.f, 0.f, 0.f)); // Top Left
					}
				}
				else
				{
					if (EnemyLocation.Y > 0)
					{
						LocationToSpawnTo = GenerateLocationIn(FVector(-850.f, 0.f, 0.f), FVector(0.f, 1550.f, 0.f)); // Bottom Right
					}
					else
					{
						LocationToSpawnTo = GenerateLocationIn(FVector(-850.f, -1550.f, 0.f), FVector(0.f)); // Bottow Left
					}
				}
			}
			else // Jump Horrizontally
			{
				if (EnemyLocation.X < 0)
				{
					if (EnemyLocation.Y > 0)
					{
						LocationToSpawnTo = GenerateLocationIn(FVector(-850.f, -1550.f, 0.f), FVector(0.f)); // Bottow Left
					}
					else
					{
						LocationToSpawnTo = GenerateLocationIn(FVector(-850.f, 0.f, 0.f), FVector(0.f, 1550.f, 0.f)); // Bottom Right
					}
				}
				else
				{
					if (EnemyLocation.Y > 0)
					{
						LocationToSpawnTo = GenerateLocationIn(FVector(0.f, -1550.f, 0.f), FVector(850.f, 0.f, 0.f)); // Top Left
					}
					else
					{
						LocationToSpawnTo = GenerateLocationIn(FVector(0.f), FVector(850.f, 1550.f, 0.f)); // Top Right
					}
				}
			}
		}
	}
	else
	{
		LocationToSpawnTo = GenerateLocationIn(FVector(-850.f, -1550.f, 0.f), FVector(850.f, 1550.f, 0.f));
	}

	// If we couldn't find location to teleport to, bail out
	if (!CanTeleportToLocation(LocationToSpawnTo))
	{
		return EBTNodeResult::Succeeded;
	}
	

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

FVector UBTTask_BlinkerEnemyBlink::GenerateLocationIn(FVector BottomLeft, FVector TopRight)
{
	FVector LocationToSpawnTo;

	// Generate random place to teleport to in the given bounds untill we get a proper one or untill we are out of attempts to find one
	int attempts = 0;
	do
	{
		LocationToSpawnTo = FVector(FMath::RandRange(BottomLeft.X, TopRight.X), FMath::RandRange(BottomLeft.Y, TopRight.Y), 260.f);
		attempts++;
	} while (!CanTeleportToLocation(LocationToSpawnTo) && attempts <= 20);
	return LocationToSpawnTo;
}

