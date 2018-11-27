// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "SpawnerActor.h"
#include "TimerManager.h"
#include "Enemy.h"
#include "Engine/World.h"

// Sets default values
ASpawnerActor::ASpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnerActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Middleman Spawned. Setting Timer"));
	FTimerHandle Handle;

	GetWorldTimerManager().SetTimer(Handle, this, &ASpawnerActor::TrySpawnAndDestroy, 1.f, true, 1.f);
}

// Called every frame
void ASpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnerActor::SetDesiredSpawningActor(TSubclassOf<class AEnemy> Enemy)
{
	EnemyToSpawn = Enemy;
}

void ASpawnerActor::TrySpawnAndDestroy()
{
	TSet<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (auto OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor->ActorHasTag("Player") || OverlappingActor->ActorHasTag("Enemy"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Collision Detected. Can't spawn. Abort and repeat."));
			return;
		}
	}
	auto SpawnedEnemy = GetWorld()->SpawnActorDeferred<AEnemy>(EnemyToSpawn, GetActorTransform());
	// TODO Set the modifiers on enemies here... When you have finished the system that is
	SpawnedEnemy->FinishSpawning(GetActorTransform());

	UE_LOG(LogTemp, Warning, TEXT("Spawned an actor. Destroying myself."));
	Destroy();
}

