// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyBallPawn.generated.h"

UCLASS()
class ARCADESHMUP_API AEnemyBallPawn : public APawn
{
	GENERATED_BODY()

		UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

public:
	// Sets default values for this pawn's properties
	AEnemyBallPawn();


	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
		class UBehaviorTree* BehaviorTree;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SequenceLaunchAt(FVector VectorToLaunch);
	
	bool bIsMovingToPoint = false;

	void SetPointDestination(FVector Destination);

	void StartAttackAt(FVector AttackDestination);
private:
	float LaunchForce = 1000000.f;
	float MovementForce = 250000.f;

	FVector Destination = FVector(0.f,0.f,250.f);
};
