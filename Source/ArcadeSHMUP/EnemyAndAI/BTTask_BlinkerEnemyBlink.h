// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_BlinkerEnemyBlink.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API UBTTask_BlinkerEnemyBlink : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Function to check if we have any collision where we are trying to teleport
	bool CanTeleportToLocation(FVector Location);

	// Function that generates a random location in a given square that does not collide with anything
	FVector GenerateLocationIn(FVector BottomLeft, FVector TopRight);
};
