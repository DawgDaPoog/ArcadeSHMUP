// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAndAI/EnemyProjectile.h"
#include "BlinkerRay.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API ABlinkerRay : public AEnemyProjectile
{
	GENERATED_BODY()

	ABlinkerRay();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ray", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Ray;
	
	UPROPERTY(Category = Materials, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class UMaterial* InactiveMaterial;

	UPROPERTY(Category = Materials, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class UMaterial* ActiveMaterial;
public:
	void ActivateRay();

	virtual void BeginPlay() override;

private:
	// Variable to check if the ray is active and should deal damage to player
	bool bIsRayActive = false;

	virtual void NotifyActorBeginOverlap(AActor * OtherActor) override;
};
