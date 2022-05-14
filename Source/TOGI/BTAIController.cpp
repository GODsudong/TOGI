// Fill out your copyright notice in the Description page of Project Settings.


#include "BTAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlacKboardComponent.h"

const FName ABTAIController::HomePosKey(TEXT("HomePos"));
const FName ABTAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ABTAIController::TargetKey(TEXT("Target"));

ABTAIController::ABTAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("BlackboardData'/Game/AI/BBoard.BBoard'"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("BehaviorTree'/Game/AI/Spider_BTree.Spider_BTree'"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
	UE_LOG(LogTemp, Log, TEXT("ABTAICONTROLLER"));
}

void ABTAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunAI();
}

void ABTAIController::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		RunBehaviorTree(BTAsset);
	}
}

void ABTAIController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr == BehaviorTreeComponent) return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
