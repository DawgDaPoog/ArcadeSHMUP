// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Drops/Drop.h"
#include "RifleDrop.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API ARifleDrop : public ADrop
{
	GENERATED_BODY()
	
		virtual void NotifyPlayerPickedUp(class AArcadeSHMUPPawn* Player) override;
	
	
};
