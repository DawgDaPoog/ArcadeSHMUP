// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropManager.generated.h"

UCLASS()
class ARCADESHMUP_API ADropManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropManager();

	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Spawnable Drops", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<class ADrop>> Drops;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitializeRandomDropAtLocation(FVector Location);
	
};
