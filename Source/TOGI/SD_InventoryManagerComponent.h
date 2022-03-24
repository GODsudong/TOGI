// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MydataStruct.h"
#include "Components/ActorComponent.h"
#include "SD_InventoryManagerComponent.generated.h"

#define Itemisvaild(itemdata) IsValid(itemdata.Icon)
#define ItemType(itemdata) itemdata.ItemType
#define ItemIsSame(first,second) ((first.ID)==(second.ID)&&(first.Icon)==(second.Icon))
#define ItemAmount(itemdata) itemdata.Amount
#define ItemMaxStackSize(itemdata) itemdata.MaxStackSize
#define ItemFreeStackSpace(itemdata) (itemdata.Amount)-(itemdata.MaxStackSize)
#define ItemEquipSlot(itemdata) itemdata.EquipmentSlot
#define ItemIsDropable(itemdata) itemdata.IsDroppable
#define ItemToItemInfo()			// 만들어둔 특정구조체가 여기에 사용되는거같은 아직 용도를 모르겠음
#define ItemToWorldItem()			// ...
#define ItemQuality(itemdata) itemdata.ItemQuality



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOGI_API USD_InventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USD_InventoryManagerComponent();
	FItemDatainfo itemDatainfo;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void LoadInventroy();
	void CreateInventorySlots(int InventroySize, int SlotPerRow);
	void AddInventorySlot(int Row, int Colum, int Slot);
	void ClearInventorySlotItem();
	void RefreshInventorySlots();
	void GetInventoryItem();
	void SetInventorySlotItem();
	void IncreaseInventorySlots();
	void DecreaseInventorySlots();
	void RemoveInventorySlot();
	void ClearInventorySlotItems();

};