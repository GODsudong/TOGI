// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerStatus.generated.h"

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
class TOGI_API APlayerStatus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerStatus();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EPlayerJob PlayerJob;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MAX_HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MAX_MP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AtkDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float shield;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SelectPlayerJob(EPlayerJob job);
};
