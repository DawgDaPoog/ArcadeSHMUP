// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FindTopPriorityAlly.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API UBTService_FindTopPriorityAlly : public UBTService
{
	GENERATED_BODY()
	
	UBTService_FindTopPriorityAlly();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
