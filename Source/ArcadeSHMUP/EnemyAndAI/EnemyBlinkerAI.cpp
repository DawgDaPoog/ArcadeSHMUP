// Copyright Vladyslav Kulinych 2018. All Rights Reserved.

#include "EnemyBlinkerAI.h"
#include "EnemyBlinker.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


void AEnemyBlinkerAI::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	EnemyClassPawn = Cast<AEnemyBlinker>(InPawn);
}

void AEnemyBlinkerAI::InitializeBlinkTo(FVector Location)
{
	// Telling blinker to teleport
	EnemyClassPawn->BlinkTo(Location);
}

void AEnemyBlinkerAI::InitializeRayTo(FVector Location)
{
	// Forwarding the initialisation of ray
	EnemyClassPawn->InitialiseRayAt(Location);
}

void AEnemyBlinkerAI::AskForBlink()
{
	// If we can blink
	if (bCanBlink)
	{
		// Change the value on the blackboard, forcing it to shut down everything else it was doing and blink
		auto BlinkKeyID = BlackboardComp->GetKeyID(FName("bShouldBlink"));
		BlackboardComp->SetValue<UBlackboardKeyType_Bool>(BlinkKeyID, true);
	}

}

void AEnemyBlinkerAI::StartBlinkCooldown()
{
	// Starting the cooldown variables
	auto BlinkKeyID = BlackboardComp->GetKeyID(FName("bShouldBlink"));
	BlackboardComp->SetValue<UBlackboardKeyType_Bool>(BlinkKeyID, false);
	bCanBlink = false;

	// Initialising timer to reset the cooldown variable
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this]() {
		bCanBlink = true;
	});

	GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, BlinkCooldown, false);
}
