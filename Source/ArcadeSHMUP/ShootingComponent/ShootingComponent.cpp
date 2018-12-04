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

	// Adjusting weapon position to it's corresponding arrow
	AdjustWeaponsPositions();
}

void UShootingComponent::OnWeaponPickup(int32 WeaponIndex)
{
	//	UE_LOG(LogTemp, Warning, TEXT("Went in the OnPickupWeapon"));
	SequencePickupWeapon(WeaponIndex);
}

void UShootingComponent::SequencePickupWeapon(const int32 &WeaponNumber)
{
	//	UE_LOG(LogTemp, Warning, TEXT("Went in the Sequence"));

	//Figure out what kind of weapon we need to spawn or upgrade depending on a weapon number
	TSubclassOf<AWeapon> WeaponToSpawn;
	FName WeaponType;
	if (WeaponNumber == 0)
	{
		WeaponToSpawn = Shotgun;
		WeaponType = FName("Shotgun");
	}
	else if (WeaponNumber == 1)
	{
		WeaponToSpawn = Machinegun;
		WeaponType = FName("Machinegun");
	}
	else if (WeaponNumber == 2)
	{
		WeaponToSpawn = Rifle;
		WeaponType = FName("Rifle");
	}
	else if (WeaponNumber == 3)
	{
		WeaponToSpawn = Lazer;
		WeaponType = FName("Lazer");
	}
	else if (WeaponNumber == 4)
	{
		WeaponToSpawn = Rocket;
		WeaponType = FName("Rocket");
	}
	else if (WeaponNumber == 5)
	{
		WeaponToSpawn = Arc;
		WeaponType = FName("Arc");
	}
	else return;

	//Figure out how many weapons of such time was already spawned
	int32 HowManyHasAlreadyBeenSpawned = CheckAmountOfSpawnedByType(WeaponType);

	
	if (HowManyHasAlreadyBeenSpawned < 2)
	{
		FWeaponArrowReference NewReference = FWeaponArrowReference();
		bool bIsFirst = (HowManyHasAlreadyBeenSpawned == 0); // See if it's first

		 // Getting the reference of an arrow for the given weapon number + it's order
		NewReference.Arrow = Cast<AArcadeSHMUPPawn>(GetOwner())->GetArrowForWeapon(WeaponNumber, bIsFirst);

		//Spawn a given weapon and save it to a reference
		NewReference.Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponToSpawn, NewReference.Arrow->GetComponentLocation(), NewReference.Arrow->GetComponentRotation());
		//Set a type for further actions
		NewReference.Type = WeaponType;
		//Add to list of weapons
		WeaponsArrows.Add(NewReference);

		UE_LOG(LogTemp, Warning, TEXT("Created, Binding"));
		//Subscribing to the Weapons OnFire delegate to start the knockback sequence
		NewReference.Weapon->OnFire.AddUniqueDynamic(this, &UShootingComponent::ReactOnWeaponFire);
	}
	else
	{
		// if we don't have available arrow for a given pickup, upgrade the weapons that are held by those arrows
		for (auto WeaponArrow : WeaponsArrows)
		{
			if (WeaponArrow.Type == WeaponType)
			{
				WeaponArrow.Weapon->Upgrade();
			}
		}
	}
}

int32 UShootingComponent::CheckAmountOfSpawnedByType(FName Type)
{
	//UE_LOG(LogTemp, Warning, TEXT("Went in the CheckAmountOfSpawned"));

	// Finding how much weapons of given type was already spawned
	int32 HowManyHasAlreadyBeenSpawned = 0;
	for (auto WeaponsArrow : WeaponsArrows)
	{
		if (WeaponsArrow.Type == Type)
		{
			HowManyHasAlreadyBeenSpawned++;
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("Finished in the CheckAmountOfSpawned"));
	return HowManyHasAlreadyBeenSpawned;

}

void UShootingComponent::AttemptShooting()
{
	// For all attached weapons, call shoot
	for (auto WeaponArrow : WeaponsArrows)
	{
		WeaponArrow.Weapon->AttemptFire();
	}
}

void UShootingComponent::DestroyAllWeapons()
{
	for (auto WeaponsArrow : WeaponsArrows)
	{
		WeaponsArrow.Weapon->Destroy();
	}
}

void UShootingComponent::AdjustWeaponsPositions()
{
	for (auto WeaponArrow : WeaponsArrows)
	{
		WeaponArrow.Weapon->SetActorRotation(WeaponArrow.Arrow->GetComponentRotation());
		WeaponArrow.Weapon->SetActorLocation(WeaponArrow.Arrow->GetComponentLocation());
	}
}

void UShootingComponent::ReactOnWeaponFire(const float KnockbackForce)
{
	// Adding impulse to player
	auto ShipMeshReferense = Cast<AArcadeSHMUPPawn>(GetOwner())->GetShipMeshComponent();
	ShipMeshReferense->AddImpulse(-ShipMeshReferense->GetForwardVector()*KnockbackForce);
}


