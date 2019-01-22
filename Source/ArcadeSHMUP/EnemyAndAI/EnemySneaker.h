// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAndAI/EnemySuicider.h"
#include "EnemySneaker.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AEnemySneaker : public AEnemySuicider
{
	GENERATED_BODY()
	
public:
	AEnemySneaker();

	// Funciton to pass on the value to which we need to change alpha of material
	UFUNCTION(BlueprintImplementableEvent, Category = "Material", meta = (DisplayName = "Change Opacity To"))
	void SetMaterialOpacityTo(const float Value);
	void SetMaterialOpacityTo_Implementation(const float Value);

protected:
	virtual void ReactToPlayer(class AArcadeSHMUPPawn* Player) override;
};
