// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "LevelBoundsVolume.h"


ALevelBoundsVolume::ALevelBoundsVolume()
{

}

void ALevelBoundsVolume::NotifyActorEndOverlap(AActor * OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	OtherActor->SetActorLocation(-OtherActor->GetActorLocation());
}
