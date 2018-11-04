// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

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

	virtual void NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit) override;

	virtual void NotifyActorBeginOverlap(AActor * OtherActor) override;

	virtual void ReactToPlayer(class AArcadeSHMUPPawn* Player);

	float HitPoints = 0.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
		class UBehaviorTree* BehaviorTree;
	
	void TakeDamage(float Damage);
};
