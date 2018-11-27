// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

class AEnemy;

UCLASS()
class ARCADESHMUP_API ASpawnPoint : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, Category = "Spawnable Enemies")
		TArray<TSubclassOf<AEnemy>> SimpleEnemies;

		UPROPERTY(EditDefaultsOnly, Category = "Spawnable Enemies")
		TArray<TSubclassOf<AEnemy>> AverageEnemies;

		UPROPERTY(EditDefaultsOnly, Category = "Spawnable Enemies")
		TArray<TSubclassOf<AEnemy>> AdvancedEnemies;

		UPROPERTY(EditDefaultsOnly, Category = "Spawning Middleman")
		TSubclassOf<class ASpawnerActor> SpawnerActor;
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TrySpawn(int CategoryIndex);

	bool SpawnEnemyOfType(int CategoryIndex);
	
};
