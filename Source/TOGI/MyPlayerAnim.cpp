// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerAnim.h"

void UMyPlayerAnim::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
}


void UMyPlayerAnim::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		PlayerMoveSpeed = LateralSpeed.Size();


		// isRoll 관리해주는 코드 추가해야함

	}
}
