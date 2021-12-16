// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

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



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	FORCEINLINE class USpringArmComponent* GetcameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
		class AWeapon* EquippedWeapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
		class AItem* ActiveOverlappingItem;

	FORCEINLINE void SetEquippedWeapon(AWeapon* WeaponToSet) { EquippedWeapon = WeaponToSet;  }
	FORCEINLINE void SetActiveoverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }
};
