// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "BTAIController.h"
#include "MyPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 0.5f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == ControllingPawn) return;

	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 1500.0f;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		bool targetOn = false;
		for (FOverlapResult OverlapResult : OverlapResults)
		{
			AMyPlayer* Player = Cast<AMyPlayer>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				targetOn = true;
				// Character면, 블랙보드에 저장한다.
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABTAIController::TargetKey, Player);

				// 디버깅 용.
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, Player->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), Player->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
		if (!targetOn)
		{
			// 임시용 바닥 콜리전 처리 하면 삭제 요망 targetOn 포함
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABTAIController::TargetKey, nullptr);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("bResult false"));
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABTAIController::TargetKey, nullptr);
	}

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}	