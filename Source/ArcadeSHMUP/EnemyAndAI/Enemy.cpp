// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "../ArcadeSHMUPPawn.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	RootComponent = Mesh;
	Mesh->SetConstraintMode(EDOFMode::XYPlane);
	Mesh->SetSimulatePhysics(true);

	Tags.Add(TEXT("Enemy"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
	if (Other->ActorHasTag("Player"))
	{
		ReactToPlayer(Cast<AArcadeSHMUPPawn>(Other));
	}
}

void AEnemy::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		ReactToPlayer(Cast<AArcadeSHMUPPawn>(OtherActor));
	}
}

void AEnemy::ReactToPlayer(AArcadeSHMUPPawn * Player)
{
	Player->TakeDamage();
}

void AEnemy::SequenceDestroy()
{
	Destroy();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::TakeDamage(float Damage)
{
	HitPoints -= Damage;

	if (HitPoints <= 0.f)
	{
		SequenceDestroy();
	}
}

