// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "MydataStruct.generated.h"

UCLASS()
class TOGI_API AMydataStruct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMydataStruct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

USTRUCT(BlueprintType)
struct FEquipmentDatainfo :public FTableRowBase{
	GENERATED_BODY()
public:
	FEquipmentDatainfo()
	{
		Max_Health = -1;
		Damage = -1;
		Defense = -1;
		Max_Stamina = -1;
		Regen_Stamina = -1;
		Critical_Chance = -1;
		Cooldown = -1;
		Attack_Delay = -1;
	}

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Max_Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Movement_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Max_Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Regen_Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Critical_Chance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Attack_Delay;





};
