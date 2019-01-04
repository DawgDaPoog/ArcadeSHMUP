// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "EnemySuicider.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

AEnemySuicider::AEnemySuicider()
{
	HitPoints = 15.f;

	PointsAwardedOnKill = 50;

	WeaponDropPriority = 1;
}

void AEnemySuicider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Adding force towards the player
	VectorNormalToPlayer.Z = 260.f;
	Mesh->AddForce(VectorNormalToPlayer*Force);

	// Clamp our movement speed if we have too much velocity on mesh
	if (GetVelocity().Size() > SpeedLimit)
	{
		Mesh->SetPhysicsLinearVelocity(GetVelocity().GetSafeNormal()*SpeedLimit);
	}
}

void AEnemySuicider::ReactToPlayer(AArcadeSHMUPPawn * Player)
{
	Super::ReactToPlayer(Player);

	SequenceDestroy();
}

void AEnemySuicider::SetForceVectorTo(FVector PlayerLocation)
{
	VectorNormalToPlayer = PlayerLocation.GetSafeNormal();

	FRotator NewRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerLocation);

	if(NewRot.Yaw <= GetActorRotation().Yaw)
	SetActorRotation(GetActorRotation() - FRotator(2.f));
	else
	SetActorRotation(GetActorRotation() + FRotator(2.f));
}
