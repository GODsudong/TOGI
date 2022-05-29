// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

class UCurveFloat;		//컴파일 시간을 줄이기 위함

UENUM()
enum class EPlayerJob : uint8
{
	PJ_KNIGHT UMETA(DisplayName = "Knight"),
	PJ_ARCHER UMETA(DisplayName = "Archer"),
	PJ_WIZARD UMETA(DisplayName = "Wizard"),
	PJ_THIEF UMETA(DisplayName = "Thief"),
	PJ_BIGSWORD UMETA(DisplayName = "Bigsword")
};

UCLASS()
class TOGI_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

	UPROPERTY(visibleAnywhere, BlueprintReadOnly,Category = Camera)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* FollowCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EPlayerJob PlayerJob;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Status")
		float MAX_HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float MAX_MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float MAX_Vital;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float Vital;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float DEF;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float ATK;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float AtkDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		float shield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
		bool isEquipped;

	void DecrementHealth(float Amount);
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const& DamageEvent,class AController* EventInstigator,AActor* DamageCauser) override;


	float InterpSpeed;
	bool bInterpToEnemy;
	void SetInterpToEnemy(bool Interp);

	UPROPERTY(VisibleAnywhere, BlueprintreadOnly,Category = "Combat")
	class AEnemyBase* CombatTarget;

	FORCEINLINE void SetCombatTarget(AEnemyBase* Target) { CombatTarget = Target; }

	FRotator GetLookAtRotationYaw(FVector Target);


	UFUNCTION()
		void DashTimeline(float Value);
	UFUNCTION()
		void DashFinish();

	FVector DirVec;
	
	//UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Widget")
	//class ASD_InventoryComponent* myInventoryComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere, Category = "Timeline")
		UCurveFloat* CurveFloat;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LMBUp();
	void LMBDown();
	bool bLMBDown;


	UFUNCTION()
		void Attack();
	UFUNCTION(BlueprintCallable)
		void AttackEnd();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anims")
		bool bAttacking;


	int ComboCount;

	float AttackDelay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
		class UAnimMontage* CombatMontage;

	void MoveForward(float value);

	void MoveRight(float value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	float MaxMinZoomInOut;
	void ZoomInOut(float WheelUpDown);

	bool isDash;

	void Dashing();

	void TabKeyDown();

	FORCEINLINE class USpringArmComponent* GetcameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
		class AWeapon* EquippedWeapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
		class AItem* ActiveOverlappingItem;

	FORCEINLINE void SetEquippedWeapon(AWeapon* WeaponToSet) { EquippedWeapon = WeaponToSet;  }
	FORCEINLINE void SetActiveoverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }

	void SelectPlayerJob(EPlayerJob job);

	void WKeyUp();
	void WKeyDown();


	bool isRun;

	float WKeyInputDelay;

	float SpeedMagnification;
};
