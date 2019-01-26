// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAndAI/EnemySuiciderAI.h"
#include "EnemyShielderAI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemyShielderAI : public AEnemySuiciderAI
{
	GENERATED_BODY()
	
protected:
	virtual void Possess(APawn *InPawn) override;

private:
	class AEnemyShielder* EnemyClassPawn;

public:
	uint8 TopAllyKeyID;
};
