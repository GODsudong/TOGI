// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "MyDataStruct.generated.h"

UENUM(BlueprintType)
enum class Type : uint8
{
	IT_EQUIPMENT UMETA(DisplayName = "Equipment"),
	IT_CONSUMABLE UMETA(DisplayName = "Consumable"),
	IT_MATERIAL UMETA(DisplayName = "Material"),
	IT_MISC UMETA(DisplayName = "Misc")
};

UENUM(BlueprintType)
enum class Quality : uint8
{
	QT_COMMON UMETA(DisplayName = "Common"),
	QT_RARE UMETA(DisplayName = "Rare"),
	QT_EPIC UMETA(DisplayName = "Epic"),
	QT_LEGEND UMETA(DisplayName = "Legend")
};

UENUM(BlueprintType)
enum class EquipSlot : uint8
{
	ES_HEAD UMETA(DisplayName = "Head"),
	ES_BODY UMETA(DisplayName = "Body"),
	ES_GLOVES UMETA(DisplayName = "Gloves"),
	ES_SHOES UMETA(DisplayName = "Shoes"),
	ES_LEFTHAND UMETA(DisplayName = "Lefthand"),
	ES_RIGHTHAND UMETA(DisplayName = "Righthand"),
	ES_ACCESSORY UMETA(DisplayName = "Accessory")
};

UENUM(BlueprintType)
enum class EquipSlotType : uint8
{
	EST_HEAD UMETA(DisplayName = "Head"),
	EST_BODY UMETA(DisplayName = "Body"),
	EST_GLOVES UMETA(DisplayName = "Gloves"),
	EST_SHOES UMETA(DisplayName = "Shoes"),
	EST_LEFTHAND UMETA(DisplayName = "Lefthand"),
	EST_RIGHTHAND UMETA(DisplayName = "Righthand"),
	EST_BELT UMETA(DisplayName = "Belt"),
	EST_BACK UMETA(DisplayName = "Back"),
	EST_NONEVIS UMETA(DisplayName = "Nonevis")
};

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
struct FItemDatainfo :public FTableRowBase {
	GENERATED_BODY()
		// 아이템에 대한 모든 정보 구조체
public:
	FItemDatainfo()
	{
		Max_HP = 0;
	}


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		Type ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		Quality ItemQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsStackable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxStackSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsDroppable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* WorldMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* EquipmentMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EquipSlot EquipmentSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EquipSlotType EquipmentSlotType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UClass* WeaponActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Max_HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Max_HP_Percent;
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
USTRUCT(BlueprintType)
struct FItemInformation
{
	GENERATED_BODY()
		// 인벤토리에 저장된 아이템 정보 구조체
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		Quality ItemQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		Type ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Amount;

};
USTRUCT(BlueprintType)
struct FItems
{
	GENERATED_BODY()
		// 드래그된 아이템에 대한 정보 구초제
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Amount;

};
USTRUCT(BlueprintType)
struct FStatusPoint
{
	GENERATED_BODY()
		// 플레이어 스탯에 관한 정보 구조체
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHpPercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RegenStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CriticalChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackDelay;

};
USTRUCT(BlueprintType)
struct FTooltipInfo
{
	GENERATED_BODY()
		// 아이템 툴팁에 대한 정보 구조체
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		Quality ItemQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		Type ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsStackable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxStackSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EquipSlot EquipmentSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Max_HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Max_HP_Percent;
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
