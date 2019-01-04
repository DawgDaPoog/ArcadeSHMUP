// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIBase.h"
#include "BallEnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API ABallEnemyAI : public AEnemyAIBase
{
	GENERATED_BODY()

	class AEnemyBallPawn* EnemyClassPawn;
public:

	virtual void Possess(APawn *InPawn) override;

	void SetOwnerMovePoint(FVector MoveTo);
	void ResetOwnerMovePoint();

	void StartAttackSequence(FVector Direction);
};
