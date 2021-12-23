// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

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
		class USphereComponent* AgroSphere;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		USphereComponent* CombatSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class AAIController* AIController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UParticleSystemComponent* HitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class USoundCue* HitSound;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	//	class SphereComponent AgroSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float MaxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float Hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		TSubclassOf<UDamageType> DamageTypeClass;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected: 
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	virtual void CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void MoveToTarget(class AMyPlayer* Target);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "A")
	bool bOverlappingCombatSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "A")
		AMyPlayer* CombatTarget;

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Combat")
	float AttackMaxTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackMinTime;

	void EnemyDead();
};
