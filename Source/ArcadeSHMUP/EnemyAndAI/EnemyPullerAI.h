// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAndAI/EnemySuiciderAI.h"
#include "EnemyPullerAI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemyPullerAI : public AEnemySuiciderAI
{
	GENERATED_BODY()

		class AEnemyPuller* EnemyClassPawn;

public:

	virtual void Possess(APawn *InPawn) override;

	void PullPlayer(class APawn* Player, float ForceModificator);
	
};
