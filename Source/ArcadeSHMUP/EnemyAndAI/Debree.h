// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Debree.generated.h"

UCLASS()
class ARCADESHMUP_API ADebree : public AEnemy
{
	GENERATED_BODY()

	UPROPERTY(Category = "Spawn", EditDefaultsOnly)
		TSubclassOf<ADebree> Debree;
public:	
	// Sets default values for this actor's properties
	ADebree();

	bool bIsSecondarySpawn = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SequenceDestroy() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
