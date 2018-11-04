// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "EnemyBallPawn.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEnemyBallPawn::AEnemyBallPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	HitPoints = 10.f;
}

// Called when the game starts or when spawned
void AEnemyBallPawn::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AEnemyBallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector ForceApply = FVector(0.f);
	if (bIsMovingToPoint)
	{
		FVector DirectionVector = Destination - GetActorLocation();
		FVector Direction = DirectionVector.GetSafeNormal();

		
		ForceApply = Direction * MovementForce;
		Mesh->AddForce(ForceApply);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("not ApplyingForce"));
	}
}



void AEnemyBallPawn::SequenceLaunchAt(FVector VectorToLaunch)
{
}

void AEnemyBallPawn::SetPointDestination(FVector Destination)
{
	this->Destination = Destination;
}

void AEnemyBallPawn::StartAttackAt(FVector AttackDestination)
{
	Mesh->AddImpulse(LaunchForce*AttackDestination);
}

