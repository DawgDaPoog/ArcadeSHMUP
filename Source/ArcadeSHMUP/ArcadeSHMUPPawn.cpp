// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ArcadeSHMUPPawn.h"
#include "ArcadeSHMUPProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "ShootingComponent/ShootingComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"

const FName AArcadeSHMUPPawn::MoveForwardBinding("UpMovement");
const FName AArcadeSHMUPPawn::MoveRightBinding("RightMovement");
const FName AArcadeSHMUPPawn::TurnClockwiseBinding("TurnClockwise");
const FName AArcadeSHMUPPawn::FireBinding("Shoot");

AArcadeSHMUPPawn::AArcadeSHMUPPawn()
{	
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	ShipMeshComponent->SetSimulatePhysics(true);

	// Cache our sound effect

	

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	ShootingComponent = CreateDefaultSubobject<UShootingComponent>(FName("ShootingComponent"));

	ArrowForShotgun1 = CreateDefaultSubobject<UArrowComponent>(FName("ArrowForShotgun1"));
	ArrowForShotgun1->SetupAttachment(RootComponent);

	ArrowForShotgun2 = CreateDefaultSubobject<UArrowComponent>(FName("ArrowForShotgun2"));
	ArrowForShotgun2->SetupAttachment(RootComponent);

	ArrowForMachinegun1 = CreateDefaultSubobject<UArrowComponent>(FName("ArrowForMachinegun1"));
	ArrowForMachinegun1->SetupAttachment(RootComponent);

	ArrowForMachinegun2 = CreateDefaultSubobject<UArrowComponent>(FName("ArrowForMachinegun2"));
	ArrowForMachinegun2->SetupAttachment(RootComponent);

	ArrowForRifle1 = CreateDefaultSubobject<UArrowComponent>(FName("ArrowForRifle1"));
	ArrowForRifle1->SetupAttachment(RootComponent);

	ArrowForRifle2 = CreateDefaultSubobject<UArrowComponent>(FName("ArrowForRifle2"));
	ArrowForRifle2->SetupAttachment(RootComponent);

	ArrowForLazer1 = CreateDefaultSubobject<UArrowComponent>(FName("ArrowForLazer1"));
	ArrowForLazer1->SetupAttachment(RootComponent);
	
	ArrowForLazer2 = CreateDefaultSubobject<UArrowComponent>(FName("ArrowForLazer2"));
	ArrowForLazer2->SetupAttachment(RootComponent);
	
	ArrowForRocket1 = CreateDefaultSubobject<UArrowComponent>(FName("ArrowForRocket1"));
	ArrowForRocket1->SetupAttachment(RootComponent);
	
	ArrowForRocket2 = CreateDefaultSubobject<UArrowComponent>(FName("ArrowForRocket2"));
	ArrowForRocket2->SetupAttachment(RootComponent);
	
	ArrowForArc1 = CreateDefaultSubobject<UArrowComponent>(FName("ArrowForArc1"));
	ArrowForArc1->SetupAttachment(RootComponent);
	
	ArrowForArc2 = CreateDefaultSubobject<UArrowComponent>(FName("ArrowForArc2"));
	ArrowForArc2->SetupAttachment(RootComponent);
}

void AArcadeSHMUPPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(TurnClockwiseBinding);
	PlayerInputComponent->BindAxis(FireBinding);

	PlayerInputComponent->BindAction(FName("Super"), IE_Pressed, this, &AArcadeSHMUPPawn::AttemptSuper);
}

void AArcadeSHMUPPawn::Tick(float DeltaSeconds)
{
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	const float ClockWiseTurnValue = GetInputAxisValue(TurnClockwiseBinding);

	const float FireValue = GetInputAxisValue(FireBinding);


	FVector MovementVector = FVector(ForwardValue*ShipThrottle*cos(0.785398*RightValue), RightValue*ShipThrottle*cos(0.785398*ForwardValue), 0.f);

	ShipMeshComponent->AddForce(MovementVector);
	
	SetActorRotation(GetActorRotation() + FRotator(0.f, ClockWiseTurnValue*TurnRate, 0.f)*DeltaSeconds);

	if (FireValue == 1.f)
	{
		AttemptFireShot();
	}
}

void AArcadeSHMUPPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AArcadeSHMUPPawn::AttemptFireShot()
{
	ShootingComponent->AttemptShooting();
}

UShootingComponent * AArcadeSHMUPPawn::GetShootingComponent()
{
	return ShootingComponent;
}

UArrowComponent* AArcadeSHMUPPawn::GetArrowForWeapon(int32 WeaponIndex, bool bIsFirst)
{
	switch(WeaponIndex)
	{
	case 0:
		if (bIsFirst)
		{
			return ArrowForShotgun1;
		}
		else
		{
			return ArrowForShotgun2;
		}
		break;
	case 1:
		if (bIsFirst)
		{
			return ArrowForMachinegun1;
		}
		else
		{
			return ArrowForMachinegun2;
		}
		break;
	case 2:
		if (bIsFirst)
		{
			return ArrowForRifle1;
		}
		else
		{
			return ArrowForRifle2;
		}
		break;
	case 3:
		if (bIsFirst)
		{
			return ArrowForLazer1;
		}
		else
		{
			return ArrowForLazer2;
		}
		break;
	case 4:
		if (bIsFirst)
		{
			return ArrowForRocket1;
		}
		else
		{
			return ArrowForRocket2;
		}
		break;
	case 5:
		if (bIsFirst)
		{
			return ArrowForArc1;
		}
		else
		{
			return ArrowForArc2;
		}
		break;
	}
	return ArrowForShotgun1;
}

void AArcadeSHMUPPawn::AttemptSuper()
{
	UE_LOG(LogTemp, Warning, TEXT("Supering"));
}


