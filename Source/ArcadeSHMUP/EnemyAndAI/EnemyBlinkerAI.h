// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAndAI/EnemyAIBase.h"
#include "EnemyBlinkerAI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemyBlinkerAI : public AEnemyAIBase
{
	GENERATED_BODY()

	class AEnemyBlinker* EnemyClassPawn;

	float BlinkCooldown = 3.5f;

	bool bCanBlink = true;
public:
	// Setting the enemy pawn class we are controling to manipulate
	virtual void Possess(APawn * InPawn) override;

	// Telling pawn to teleport
	void InitializeBlinkTo(FVector Location);

	// Telling blinker to initialize the ray
	void InitializeRayTo(FVector Location);

	// Used by EnemyBlinker to try and initialize blink when it's hurt
	void AskForBlink();

	// Starts cooldown on blink
	void StartBlinkCooldown();
};
