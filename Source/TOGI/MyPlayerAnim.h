// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class TOGI_API UMyPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
	void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PlayerMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isRun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isRoll;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class AMyPlayer* player;

};
