// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIBase.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemyAIBase : public AAIController
{
	GENERATED_BODY()

protected:
	AEnemyAIBase();

	UPROPERTY(Transient)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BehaviorComp;

	class AEnemy* Pawn;
public:
	uint8 EnemyKeyID;

	FVector GetOwnerPosition();

	virtual void Possess(APawn *InPawn) override;

	class APawn* GetPossessedPawn();
};
