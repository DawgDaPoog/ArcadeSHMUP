// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Drops/Drop.h"
#include "MachinegunDrop.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API AMachinegunDrop : public ADrop
{
	GENERATED_BODY()
	
		virtual void NotifyPlayerPickedUp(class AArcadeSHMUPPawn* Player) override;
	
	
};
