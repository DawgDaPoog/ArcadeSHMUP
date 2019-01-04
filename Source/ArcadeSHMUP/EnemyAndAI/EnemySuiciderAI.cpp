// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "EnemySuiciderAI.h"
#include "EnemySuicider.h"


void AEnemySuiciderAI::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	EnemyClassPawn = Cast<AEnemySuicider>(InPawn);
}

void AEnemySuiciderAI::SetPerTickVectorValueTowards(FVector PlayerLocation)
{
	EnemyClassPawn->SetForceVectorTo(PlayerLocation);
}


