// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEnemyDelegate, const int, Score, AEnemy*, EnemyReference);

UCLASS()
class ARCADESHMUP_API AEnemy : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Mesh
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

	// Particles
	UPROPERTY(Category = ParticleEffects, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* ParticlesOnDeath;

	// Checking if we hit a player. If we did, react with ReactToPlayer
	virtual void NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit) override;

	// Same as Hit, but if overlapping
	virtual void NotifyActorBeginOverlap(AActor * OtherActor) override;

	// Reacting to player that got hit. Usually just deal damage
	virtual void ReactToPlayer(class AArcadeSHMUPPawn* Player);

	// Enemy health
	//UPROPERTY(EditAnywhere, meta = (BlueprintProtected = "true"))
	float HitPoints = 0.f;

	// How much points do you get when killing this enemy
	int PointsAwardedOnKill = 0;

	/* 
	* Priority of dropping a weapon upon death  
	* 0 - Neven drops a weapon,
	* 1 - Simple Enemy, 2% regular chance to drop
	* 2 - Average Enemy, 10% regular chance to drop
	* 3 - Advanced Enemy, 20% regular chance to drop
	* 4 - Special Enemy, Always drops
	**/
	int WeaponDropPriority = 0;
	
	//* Priority of dropping a modification upon death  (Under development)
	int ModificationDropPriority = 0;

	// Sequence for destroying the enemy
	virtual void SequenceDestroy();

	// Health modificator
	float HealthModificator = 1.f;

	// Variable to determine if the enemy is invincible or not
	bool bIsInvincible = false;

	// Reference to the game mode in case we need something from it or say to it
	class AArcadeSHMUPGameMode* CurrentGameMode;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Behavior tree
	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
		class UBehaviorTree* BehaviorTree;
	
	// Is called when enemy takes damage and determines if enemy has died with the amount of taken damage or not
	void TakeDamage(float Damage);

	// 
	FEnemyDelegate OnDeath;

	void SetHealthModificator(float Modificator);

	virtual void UpgradeToLevel(int32 Level);
};
