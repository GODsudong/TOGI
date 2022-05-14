// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SDBTTask_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class TOGI_API USDBTTask_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USDBTTask_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
