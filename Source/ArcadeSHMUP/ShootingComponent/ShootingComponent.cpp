// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "ShootingComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "../ArcadeSHMUPPawn.h"
#include "Components/ArrowComponent.h"
#include "Weapon.h"
// Sets default values for this component's properties
UShootingComponent::UShootingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShootingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	
}


// Called every frame
void UShootingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UShootingComponent::OnWeaponPickup(int32 WeaponNumber)
{
	if (WeaponNumber == 0)
	{
		int32 HowManyHasAlreadyBeenSpawned = CheckAmountOfSpawnedByType(FName("Shotgun"));
		//Shotgun picked up
		
		if (HowManyHasAlreadyBeenSpawned == 0 || HowManyHasAlreadyBeenSpawned == 1)
		{
			FWeaponArrowReference NewReference = FWeaponArrowReference();
			bool bIsFirst = (HowManyHasAlreadyBeenSpawned == 0);

			NewReference.Arrow = Cast<AArcadeSHMUPPawn>(GetOwner())->GetArrowForWeapon(0,true);
			NewReference.Weapon = GetWorld()->SpawnActor<AWeapon>(Shotgun, NewReference.Arrow->GetComponentLocation(), NewReference.Arrow->GetComponentRotation());
			NewReference.Type = FName("Shotgun");
		}
		else
		{
			for (auto WeaponArrow : WeaponsArrows)
			{
				if (WeaponArrow.Type == FName("Shotgun"))
				{
					WeaponArrow.Weapon->Upgrade();
				}

			}
		}

	}
}

int32 UShootingComponent::CheckAmountOfSpawnedByType(FName Type)
{
	int32 HowManyHasAlreadyBeenSpawned = 0;
	for (auto WeaponsArrow : WeaponsArrows)
	{
		if (WeaponsArrow.Type == Type)
		{
			HowManyHasAlreadyBeenSpawned++;
		}
	}
	return HowManyHasAlreadyBeenSpawned;
}

void UShootingComponent::AdjustWeaponsPositions()
{

}


