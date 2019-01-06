// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAndAI/EnemyAIBase.h"
#include "EnemyShooterAI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemyShooterAI : public AEnemyAIBase
{
	GENERATED_BODY()

	UPROPERTY(Category = Shooting, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ShootingDelay;

	class AEnemyShooter* EnemyClassPawn;
public:
	AEnemyShooterAI();

	virtual void Possess(APawn *InPawn) override;

	void CallShootAt(FVector Location);

	void SetForceTo(FVector Location);

	void SetShootingDelayModificator(float Modificator);

	float GetShootingDelay() const;
};
