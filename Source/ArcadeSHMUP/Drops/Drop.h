// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Drop.generated.h"


/*
* Default class for every pickup
**/
UCLASS()
class ARCADESHMUP_API ADrop : public AActor
{
	GENERATED_BODY()

	// Standart mesh
	UPROPERTY(Category = "Mesh", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	// Pickup's idle glow
	UPROPERTY(Category = "Particles", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* Glow;
public:	
	// Sets default values for this actor's properties
	ADrop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// Called when player interacts with it
	virtual void NotifyPlayerPickedUp(class AArcadeSHMUPPawn* Player);
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
