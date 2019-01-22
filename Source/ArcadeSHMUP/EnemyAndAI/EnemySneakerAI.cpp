// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySneakerAI.h"
#include "EnemySneaker.h"

void AEnemySneakerAI::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	EnemyClassPawn = Cast<AEnemySneaker>(InPawn);
}

void AEnemySneakerAI::SetShipsOpacityTo(float Value)
{
	EnemyClassPawn->SetMaterialOpacityTo(Value);
}

