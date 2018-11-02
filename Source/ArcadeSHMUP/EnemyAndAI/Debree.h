// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Debree.generated.h"

UCLASS()
class ARCADESHMUP_API ADebree : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = "Spawn", EditDefaultsOnly)
		TSubclassOf<ADebree> Debree;
public:	
	// Sets default values for this actor's properties
	ADebree();

	bool bIsSecondarySpawn = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Die();

	
	
};
