// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "DropManager.h"
#include "Drop.h"
#include "Engine/World.h"

// Sets default values
ADropManager::ADropManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADropManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADropManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADropManager::InitializeRandomDropAtLocation(FVector Location)
{
	if (Drops.Num() == 0) return;

	int DropIndex = FMath::RandRange(0, Drops.Num()-1);

	GetWorld()->SpawnActor<ADrop>(Drops[DropIndex], Location, FRotator(0.f));
}

