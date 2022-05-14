// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_IsInAttackRange.h"
#include "BTAIController.h"
#include "MyPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return false;

	AMyPlayer* Target = Cast<AMyPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABTAIController::TargetKey));
	if (nullptr == Target) return false;

	bool bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);
	return bResult;
}

