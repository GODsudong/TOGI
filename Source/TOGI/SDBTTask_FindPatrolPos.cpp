// Fill out your copyright notice in the Description page of Project Settings.


#include "SDBTTask_FindPatrolPos.h"
#include "BTAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

USDBTTask_FindPatrolPos::USDBTTask_FindPatrolPos()
{

	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type USDBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Log, TEXT("FindPatrol Tick"));
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		UE_LOG(LogTemp, Log, TEXT("Pawn Missing"));
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
	{
		UE_LOG(LogTemp, Log, TEXT("HomePos Missing"));
		return EBTNodeResult::Failed;

	}

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ABTAIController::HomePosKey);
	FNavLocation NextPatrol;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextPatrol))
	{
		UE_LOG(LogTemp, Log, TEXT("Succeeded"));
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ABTAIController::PatrolPosKey, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}
	UE_LOG(LogTemp, Log, TEXT("FindPatrol Tick Failed"));
	return EBTNodeResult::Failed;
}