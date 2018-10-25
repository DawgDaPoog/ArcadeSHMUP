// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootingComponent.generated.h"

USTRUCT()
struct FWeaponArrowReference
{
	GENERATED_USTRUCT_BODY();

		class AWeapon* Weapon;

		class UArrowComponent* Arrow;

		FName Type;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADESHMUP_API UShootingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootingComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeapon> Shotgun;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AWeapon> Machinegun;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AWeapon> Rifle;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AWeapon> Lazer;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AWeapon> Rocket;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AWeapon> Arc;

	void OnWeaponPickup(int32 WeaponNumber);
	int32 CheckAmountOfSpawnedByType(FName &Type);
	// 0 - shotgun, 1 - Machinegun, 2 - Rifle, 3 - Lazer, 4 - Rocket, 5 - Arc
	
private:
	void AdjustWeaponsPositions();

	
	TSet<FWeaponArrowReference> WeaponsArrows;
};
