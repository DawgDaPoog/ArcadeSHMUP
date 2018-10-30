// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Drops/Drop.h"
#include "ArcDrop.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AArcDrop : public ADrop
{
	GENERATED_BODY()
	
	virtual void NotifyPlayerPickedUp(class AArcadeSHMUPPawn* Player) override;
	
	
};
