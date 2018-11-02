// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "Debree.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
ADebree::ADebree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetConstraintMode(EDOFMode::XYPlane);
	Mesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ADebree::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetPhysicsLinearVelocity(FMath::VRand().GetSafeNormal()*500.f);
}

// Called every frame
void ADebree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADebree::Die()
{
	if (!bIsSecondarySpawn && Debree)
	{
		for (int i = 0; i <= FMath::RandRange(3, 6); i++)
		{
			
			FTransform DebreeTransform = FTransform(FRotator(0.f, FMath::RandRange(0.f, 360.f), 0.f), GetActorLocation(), FVector(FMath::RandRange(0.2f, 0.5f), FMath::RandRange(0.2f, 0.5f), 1.f));
			ADebree* DebreeActor = GetWorld()->SpawnActor<ADebree>(Debree,DebreeTransform);
			
			DebreeActor->bIsSecondarySpawn = true;
		}
	}
	Destroy();
}

