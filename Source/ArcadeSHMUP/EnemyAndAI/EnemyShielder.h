// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAndAI/EnemySuicider.h"
#include "EnemyShielder.generated.h"

// Struct that holds reference to actors that need to recieve their particles
USTRUCT()
struct FParticlesToActor
{
	GENERATED_USTRUCT_BODY();

	class AActor* Enemy = nullptr;

	class UParticleSystemComponent* Particles = nullptr;
};

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemyShielder : public AEnemySuicider
{
	GENERATED_BODY()

	AEnemyShielder();

	// Volume that is used to trigger other enemies invulnurability and health regeneration
	UPROPERTY(Category = "Volume", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* ShieldVolume;

	// How much health it renenerates for self and other enemies in vicinity
	UPROPERTY(EditDefaultsOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	float VolumeHealthPerSecondRegeneration = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "Particles", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ParticlesToEmmit;
public:
	virtual void Tick(float DeltaTime) override;

	// Function to forward the initialisation of particles to all actors in range
	void EmmitShieldParticleEffectsTo(AActor* Actor);

	// Reacting to player that got hit. 
	virtual void ReactToPlayer(class AArcadeSHMUPPawn* Player);
private:
	// Triggered when ShieldVolume has started overlapping something
	UFUNCTION()
	void OnShieldVolumeOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Triggered when ShieldVolume has ended overlapping something
	UFUNCTION()
	void OnShieldVolumeOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void RemoveInvincibilityFrom(AActor * OtherActor);

	// Overriding to check for all currently overlapped enemies and make then vulnurable again before destroying this enemy
	virtual void SequenceDestroy() override;

	TArray<FParticlesToActor> ParticlesToActorArray;
};
