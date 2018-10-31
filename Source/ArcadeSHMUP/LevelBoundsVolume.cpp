// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "LevelBoundsVolume.h"


ALevelBoundsVolume::ALevelBoundsVolume()
{

}

void ALevelBoundsVolume::NotifyActorEndOverlap(AActor * OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	OtherActor->SetActorLocation(FVector(-OtherActor->GetActorLocation().X - FMath::Sign(-OtherActor->GetActorLocation().X)*20.f,-OtherActor->GetActorLocation().Y - FMath::Sign(-OtherActor->GetActorLocation().Y)*20.f , OtherActor->GetActorLocation().Z));
}
