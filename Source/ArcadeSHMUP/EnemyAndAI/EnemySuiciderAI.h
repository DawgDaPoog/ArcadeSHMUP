// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemySuiciderAI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemySuiciderAI : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BehaviorComp;

	class AEnemySuicider* Pawn;
public:
	AEnemySuiciderAI();

	virtual void Possess(APawn *InPawn) override;

	uint8 EnemyKeyID;

	void SetPerTickVectorValueTowards(FVector PlayerLocation);

	FVector GetOwnerPosition();
};
