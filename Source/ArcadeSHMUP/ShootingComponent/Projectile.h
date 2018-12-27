// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class ARCADESHMUP_API AProjectile : public AActor
{
	GENERATED_BODY()
	
		/** Sphere collision component */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ProjectileMesh;

		
public:	
	// Sets default values for this actor's properties
	AProjectile();

	/** Returns ProjectileMesh subobject **/
	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float ProjectileInitialSpeed = 3000.f;
	float ProjectileMaxSpeed = ProjectileInitialSpeed;
	float ProjectileAcceleration = 0.f; 

	float ProjectileCurrentSpeed = ProjectileInitialSpeed;

	float Damage = 0.f;

	virtual void NotifyActorBeginOverlap(AActor * OtherActor) override;
	virtual void ReactToEnemy(AActor* Enemy);

	void Move(float DeltaTime);

	bool bMoving = true;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDamage(float DamageToSet);
	
	void SetProjectileSpeedModificator(float Modificator);

	void SetProjectileSizeModificator(float Modificator);
};
