// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerActor.generated.h"

/*
* A middleman class to spawn an enemy
**/
UCLASS()
class ARCADESHMUP_API ASpawnerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerActor();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Setting the actor that needs to be spawned by this actor
	void SetDesiredSpawningActor(TSubclassOf<class AEnemy> Enemy);
	
private:
	// Class of an enemy to spawn
	TSubclassOf<class AEnemy> EnemyToSpawn;

	// Attempting to spawn an actor if there is no collision on it. If we did, destroy this actor, ending the cycle of repeating the attempt of spawning
	void TrySpawnAndDestroy();
};
