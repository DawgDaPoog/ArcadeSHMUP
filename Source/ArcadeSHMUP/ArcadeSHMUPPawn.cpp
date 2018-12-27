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
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "ShootingComponent/ShootingComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "ArcadeSHMUPGameMode.h"
#include "Particles/ParticleSystemComponent.h"

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

	// Creating a default particle system for when we get hurt
	InvulnurabilityParticles = CreateDefaultSubobject<UParticleSystemComponent>(FName("InvulnurabilityParticles"));
	InvulnurabilityParticles->SetAutoActivate(false); // We will activate it only when needed
	InvulnurabilityParticles->SetupAttachment(RootComponent);

	// Component to handle shooting
	ShootingComponent = CreateDefaultSubobject<UShootingComponent>(FName("ShootingComponent"));

	// Arrows to spawn weapons at
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

	// Super key binding
	PlayerInputComponent->BindAction(FName("Super"), IE_Pressed, this, &AArcadeSHMUPPawn::AttemptSuper);
}

void AArcadeSHMUPPawn::Tick(float DeltaSeconds)
{
	// Checking movement values
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Checking turning value
	const float ClockWiseTurnValue = GetInputAxisValue(TurnClockwiseBinding);

	// Checking fire value
	const float FireValue = GetInputAxisValue(FireBinding);

	// Movement vector
	FVector MovementVector = FVector(ForwardValue*ShipThrottle*cos(0.785398*RightValue), RightValue*ShipThrottle*cos(0.785398*ForwardValue), 0.f);

	// Adding movement force
	ShipMeshComponent->AddForce(MovementVector);
	
	// Changing rotation
	SetActorRotation(GetActorRotation() + FRotator(0.f, ClockWiseTurnValue*TurnRate, 0.f)*DeltaSeconds);

	// Firing if we have proper fire value
	if (FireValue == 1.f)
	{
		AttemptFireShot();
	}
}

void AArcadeSHMUPPawn::BeginPlay()
{
	Super::BeginPlay();

	if (ShootingComponent)
	{
		int RandWeaponIndex = FMath::RandRange(0, 2);
		if (RandWeaponIndex == 2)
		{
			RandWeaponIndex = 3;
		}
		ShootingComponent->OnWeaponPickup(0);
	}
}

void AArcadeSHMUPPawn::AttemptFireShot()
{
	// Telling a shooting component to start shooting
	ShootingComponent->AttemptShooting();
}

UShootingComponent * AArcadeSHMUPPawn::GetShootingComponent()
{
	return ShootingComponent;
}

UArrowComponent* AArcadeSHMUPPawn::GetArrowForWeapon(int32 WeaponIndex, bool bIsFirst)
{
	// Determining for which arrow we are calling and retirning it
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

void AArcadeSHMUPPawn::TakeDamage()
{
	// If invincible, don't take any damage
	if (bIsInvincible) return;

	// Decrease HP if not invincible
	HowMuchHPLeft--;

	// If we have no hp left, destroy this actor and end current session
	if (HowMuchHPLeft <= 0)
	{
		Cast<AArcadeSHMUPGameMode>(GetWorld()->GetAuthGameMode())->EndGameCycle();
		ShootingComponent->DestroyAllWeapons();
		Destroy();
	}


	// Setting invincibility for a short time after being damaged
	bIsInvincible = true;

	// Showing particles that signify that player is invulnurable
	InvulnurabilityParticles->Activate();

	// Timer handler and delegate to set invincibility end timer
	FTimerHandle Handle;
	FTimerDelegate Delegate;

	// Setting a delegate
	Delegate.BindLambda([&]()
	{
		InvulnurabilityParticles->Deactivate();
		bIsInvincible = false;
	});

	// Starting a timer to end invincibility after 1.5 sec
	GetWorldTimerManager().SetTimer(Handle, Delegate, 1.5f, false);
}


