// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOGI_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
		void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class AEnemyBase* Enemybase;


};
