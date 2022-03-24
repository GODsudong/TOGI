// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MydataStruct.h"
#include "Components/ActorComponent.h"
#include "SD_InventoryComponent.generated.h"

// itemdata의 배열에 인덱스로 접근 icon 유무에 대한 것으로 존재 여부 판단
#define itemisvaild(itemdata) IsValid(itemdata.Icon)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOGI_API USD_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USD_InventoryComponent();



	TArray<FItemDatainfo> ItemData;				// 모든 아이템의 데이터 정보
	TArray<FItemDatainfo> InventoryData;		// 인벤토리 데이터 정보
	FItemDatainfo InitinventoryData;			// 인벤토리 초기화에 사용될 구조체 정보
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame


	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	FItemDatainfo GetItemData(int id);
	UFUNCTION()
	void SetInventoryItem(int Slot, FItemDatainfo Item);
	UFUNCTION()
	int GetEmptyInventorySpace();
	UFUNCTION()
	int GetInventoryItemCount();
	UFUNCTION()
	void IncreaseInventorySize(int Amount);
	UFUNCTION()
	void DecreaseInventorySize(int Amount);
	UFUNCTION()
	void LoadInventoryItems(int InventorySize, FItemDatainfo InventroyItem);
	UFUNCTION()
	TArray<FItemDatainfo> GetInventoryItems();
	UFUNCTION()
	void InitInventory(int InventorySize);
	UFUNCTION()
	void ClearInventoryItem(int SlotCount);
};
