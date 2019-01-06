// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckForPlayer.generated.h"

/**
 * BTService that is universal for all enemies that finds a player and sets it to the blackboard key
 */
UCLASS()
class ARCADESHMUP_API UBTService_CheckForPlayer : public UBTService
{
	GENERATED_BODY()

	UBTService_CheckForPlayer();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
