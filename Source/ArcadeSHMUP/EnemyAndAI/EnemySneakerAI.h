// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAndAI/EnemySuiciderAI.h"
#include "EnemySneakerAI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemySneakerAI : public AEnemySuiciderAI
{
	GENERATED_BODY()
	
	class AEnemySneaker* EnemyClassPawn;
public:
	virtual void Possess(APawn *InPawn) override;

	void SetShipsOpacityTo(float Value);
};
