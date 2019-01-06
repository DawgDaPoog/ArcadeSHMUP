// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAndAI/Enemy.h"
#include "EnemySuicider.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemySuicider : public AEnemy
{
	GENERATED_BODY()

	AEnemySuicider();

	virtual void Tick(float DeltaTime) override;

	FVector VectorNormalToPlayer;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Force = 80000.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaximumVelocity = 700.f;

	virtual void ReactToPlayer(class AArcadeSHMUPPawn* Player) override;
public:
	void SetForceVectorTo(FVector PlayerLocation);
};
