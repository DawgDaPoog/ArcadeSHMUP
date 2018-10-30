// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "EnemyBallPawn.h"


// Sets default values
AEnemyBallPawn::AEnemyBallPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

// Called to bind functionality to input
void AEnemyBallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

