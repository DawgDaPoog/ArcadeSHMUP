// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Drop.generated.h"

UCLASS()
class ARCADESHMUP_API ADrop : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = "Particles", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* Glow;
public:	
	// Sets default values for this actor's properties
	ADrop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void NotifyPlayerPickedUp(class AArcadeSHMUPPawn* Player);
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
