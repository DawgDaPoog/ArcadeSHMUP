// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAIBase.h"
#include "EnemySuiciderAI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemySuiciderAI : public AEnemyAIBase
{
	GENERATED_BODY()

	class AEnemySuicider* EnemyClassPawn;
public:

	virtual void Possess(APawn *InPawn) override;

	void SetPerTickVectorValueTowards(FVector PlayerLocation);
};
