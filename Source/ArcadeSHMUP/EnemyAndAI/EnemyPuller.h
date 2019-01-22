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

	UPROPERTY(EditDefaultsOnly, Categoy = "Pull", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ParticlesAtPull;

public:
	AEnemyPuller();

	void PullTowardsSelf(AArcadeSHMUPPawn* Player);

	UFUNCTION(BlueprintImplementableEvent, Category = "Visual")
	void EmmitParticleEffectsTo(const AActor* Actor);
};
