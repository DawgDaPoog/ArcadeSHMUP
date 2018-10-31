// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BallEnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API ABallEnemyAI : public AAIController
{
	GENERATED_BODY()


	UPROPERTY(Transient)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BehaviorComp;

	class AEnemyBallPawn* Pawn;
public:
	ABallEnemyAI();

	virtual void Possess(APawn *InPawn) override;
	
	uint8 EnemyKeyID;

	FVector GetOwnerPosition();

	void SetOwnerMovePoint(FVector MoveTo);
	void ResetOwnerMovePoint();

	void StartAttackSequence(FVector Direction);
};
