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

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = ParticleEffects, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* ParticlesOnDeath;

	virtual void NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit) override;

	virtual void NotifyActorBeginOverlap(AActor * OtherActor) override;

	virtual void ReactToPlayer(class AArcadeSHMUPPawn* Player);

	float HitPoints = 0.f;

	int PointsAwardedOnKill = 0;

	virtual void SequenceDestroy();

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
		class UBehaviorTree* BehaviorTree;
	
	void TakeDamage(float Damage);

	FEnemyDelegate OnDeath;

	
};
