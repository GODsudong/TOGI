// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"
	
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UENUM(BlueprintType)
enum class EEnemyMovementStatus :uint8
{
	EMS_Idle			UMETA(DisplayName = "Idle"),
	EMS_MoveToTarget	UMETA(DisPlayName = "MoveToTarget"),
	EMS_Attacking		UMETA(DisplayName = "Attacking"),
	EMS_Dead			UMETA(DisPlayName = "Dead"),
	EMS_MAX				UMETA(DisplayName = "DefeaultMAX")

};


UCLASS()
class TOGI_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	EEnemyMovementStatus Enemymovemonetstatus;

	FORCEINLINE void SetEnemyMovementStatus(EEnemyMovementStatus status) { Enemymovemonetstatus = status; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class AAIController* AIController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UParticleSystemComponent* HitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class USoundCue* HitSound;

	UFUNCTION(BlueprintCallable)
		void OnAttackMontageEnded();

	UFUNCTION(BlueprintCallable)
	void Attack();

	FOnAttackEndDelegate OnAttackEnd;

	void EnemyDead();

	UPROPERTY(VisibleAnywhere, Category = "UI")
		class UWidgetComponent* HPBarWidget;

protected: 
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
	float HP;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsAttacking;

};
