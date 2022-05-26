// Fill out your copyright notice in the Description page of Project Settings.


#include "SDBTTask_Attack.h"
#include "BTAIController.h"
#include "EnemyBase.h"


USDBTTask_Attack::USDBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

// 3가지 값을 리턴한다 InProgress 대기, Failed 실패, Succeeded 성공
EBTNodeResult::Type USDBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//UE_LOG(LogTemp, Log, TEXT("1111111111"));
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto EnemyBase = Cast<AEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == EnemyBase)
		return EBTNodeResult::Failed;

	//UE_LOG(LogTemp, Log, TEXT("22222222222"));

	EnemyBase->OnAttackEnd.AddLambda([this]()->void {
		//UE_LOG(LogTemp, Log, TEXT("333333333"));
		IsAttacking = false;
		//UE_LOG(LogTemp, Log, TEXT("ISAttacking :: %s"), this->IsAttacking ? TEXT("true") : TEXT("false"));
		});

	EnemyBase->Attack();
	IsAttacking = true;

	return EBTNodeResult::InProgress;
}

void USDBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	// UE_LOG(LogTemp, Log, TEXT("ISAttacking :: %s"), this->IsAttacking ? TEXT("true") : TEXT("false"));

	if (!IsAttacking)
	{
		UE_LOG(LogTemp, Log, TEXT("EnemyAttackSucceeded"));
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}