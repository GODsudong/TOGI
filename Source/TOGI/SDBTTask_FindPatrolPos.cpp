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
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;
	// Homepos 위치 값 Controller에서 방법을 찾아서 초기화 하는 방식으로 수정할것 수정하고 삭제
	FVector Hompos;
	ControllingPawn->GetTransform().TransformPosition(Hompos);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(ABTAIController::HomePosKey, Hompos);

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ABTAIController::HomePosKey);
	FNavLocation NextPatrol;
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, 500.0f, NextPatrol))
	{
		UE_LOG(LogTemp, Log, TEXT("Succeeded"));
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ABTAIController::PatrolPosKey, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}
	UE_LOG(LogTemp, Log, TEXT("FindPatrol Tick Failed"));
	return EBTNodeResult::Failed;
}