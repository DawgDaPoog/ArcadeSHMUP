// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "EnemyShooterAI.h"
#include "EnemyShooter.h"

AEnemyShooterAI::AEnemyShooterAI()
{
	ShootingDelay = 2.f;
}

void AEnemyShooterAI::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	EnemyClassPawn = Cast<AEnemyShooter>(InPawn);
}


void AEnemyShooterAI::CallShootAt(FVector Location)
{
	// EnemyClassPawn->ShootAt(Location);
}

void AEnemyShooterAI::SetForceTo(FVector Location)
{
	if (EnemyClassPawn)
	{
		EnemyClassPawn->SetForceVectorTo(Location);
	}
}

void AEnemyShooterAI::SetShootingDelayModificator(float Modificator)
{
	ShootingDelay *= Modificator;
}

float AEnemyShooterAI::GetShootingDelay() const
{
	return ShootingDelay;
}
