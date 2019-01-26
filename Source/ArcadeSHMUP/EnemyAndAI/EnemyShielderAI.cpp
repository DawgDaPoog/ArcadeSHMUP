// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyShielderAI.h"
#include "EnemyShielder.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

void AEnemyShielderAI::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	EnemyClassPawn = Cast<AEnemyShielder>(InPawn);

	if (Pawn && Pawn->BehaviorTree)
	{
		TopAllyKeyID = BlackboardComp->GetKeyID("Ally");
	}
}
