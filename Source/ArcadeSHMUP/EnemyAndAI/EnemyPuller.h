// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAndAI/EnemySuicider.h"
#include "EnemyPuller.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemyPuller : public AEnemySuicider
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Pull", meta = (AllowPrivateAccess = "true"))
	float PullForce = 100000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Pull", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ParticlesAtPull;

	class APawn* FocusedOnPlayer;
public:
	AEnemyPuller();

	virtual void Tick(float DeltaTime) override;

	void PullTowardsSelf(APawn* Player, float ForceModificator);

	UFUNCTION(BlueprintImplementableEvent, Category = "Visual")
	void EmmitParticleEffectsTo(const AActor* Actor);

protected:
	virtual void ReactToPlayer(class AArcadeSHMUPPawn* Player) override;
};
