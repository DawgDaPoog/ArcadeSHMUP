// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "LevelBoundsVolume.h"


ALevelBoundsVolume::ALevelBoundsVolume()
{

}

void ALevelBoundsVolume::NotifyActorEndOverlap(AActor * OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
	// Setting an actor on the other side of the map if it is player or enemy
	if (OtherActor->ActorHasTag(FName("Player")) || OtherActor->ActorHasTag(FName("Enemy")))
	{
		OtherActor->SetActorLocation(FVector(-OtherActor->GetActorLocation().X - FMath::Sign(-OtherActor->GetActorLocation().X)*2.f, -OtherActor->GetActorLocation().Y - FMath::Sign(-OtherActor->GetActorLocation().Y)*2.f, OtherActor->GetActorLocation().Z));
	}
}
