// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "LevelBoundsVolume.generated.h"

/**
 * 
 */
UCLASS()
class ARCADESHMUP_API ALevelBoundsVolume : public AVolume
{
	GENERATED_BODY()

		ALevelBoundsVolume();

		// Upon ending overlapping with an enemy or player, set them on the other side of the current map
		virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
};
