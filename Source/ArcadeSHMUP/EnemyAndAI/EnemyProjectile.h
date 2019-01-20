// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.generated.h"

UCLASS()
class ARCADESHMUP_API AEnemyProjectile : public AActor
{
	GENERATED_BODY()

		UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles", meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* Particles;
public:	
	// Sets default values for this actor's properties
	AEnemyProjectile();

protected:

	virtual void NotifyActorBeginOverlap(AActor * OtherActor) override;

	float ProjectileInitialSpeed = 500.f;

	bool bIsMoving = true;

	class UParticleSystemComponent* GetParticles() const;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void SetProjectileSpeedModificator(float Modificator);
};
