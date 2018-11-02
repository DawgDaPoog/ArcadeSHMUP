// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyBallPawn.generated.h"

UCLASS()
class ARCADESHMUP_API AEnemyBallPawn : public AEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBallPawn();


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SequenceLaunchAt(FVector VectorToLaunch);
	
	bool bIsMovingToPoint = false;

	void SetPointDestination(FVector Destination);

	void StartAttackAt(FVector AttackDestination);
private:
	float LaunchForce = 1000000.f;
	float MovementForce = 250000.f;

	FVector Destination = FVector(0.f,0.f,250.f);
};
