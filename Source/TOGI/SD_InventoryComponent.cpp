// Fill out your copyright notice in the Description page of Project Settings.


#include "SD_InventoryComponent.h"
#include "Components/WidgetComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
// Sets default values for this component's properties
USD_InventoryComponent::USD_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//InventoryWidget = ConstructorHelpersInternal::FindOrLoadObject<UUserWidget>("/Game/NEW0524UI/UI_Window/InventoryEquiment_Window.InventoryEquiment_Window_C");
	// ...
}


// Called when the game starts
void USD_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USD_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// ...
}


FItemDatainfo USD_InventoryComponent::GetItemData(int itemSlot)
{
	//itemSlot에 인덱스에 해당하는 배열의 아이템 정보를 반환함
	if (itemisvaild(InventoryData[itemSlot]))
	{
		return InventoryData[itemSlot];
	}
	return FItemDatainfo();
}

void USD_InventoryComponent::SetInventoryItem(int Slot, FItemDatainfo Item)
{
	InventoryData[Slot] = Item;
}

int USD_InventoryComponent::GetEmptyInventorySpace()
{
	// 인벤토리의 빈공간을 카운팅하여 반환함
	int LocalCount = 0;	
	for (auto& i : InventoryData)
	{
		if (!(itemisvaild(i)))
		{
			return LocalCount;
		}
		LocalCount++;
	}
	return 0;
}

int USD_InventoryComponent::GetInventoryItemCount()
{
	// 인벤토리의 아이템 존재 갯수를 카운팅하여 반환함
	int Localcount = 0;
	for (auto& i : InventoryData)
	{
		if (itemisvaild(i))
		{
			Localcount++;
		}
	}
	return Localcount;
}

void USD_InventoryComponent::IncreaseInventorySize(int Amount)
{
	// 인벤토리의 크기를Amount만큼 증가시킴
	for (int i = 0; i < Amount; i++)
	{
		InventoryData.Add(InitinventoryData);
	}
}

void USD_InventoryComponent::DecreaseInventorySize(int Amount)
{
	// 인벤토리의 크기를 감소시키는 함수
}

void USD_InventoryComponent::LoadInventoryItems(int InventorySize, FItemDatainfo InventroyItem)
{
	// 인벤토리를 켰을때 작동할 함수 인벤토리의 기초적인 정렬도 적용된다
	TArray<FItemDatainfo> tempInventoryItems = InventoryData;
	InventoryData.Empty();
	for (int i = 0; i < InventorySize; i++)
	{
		InventoryData.Add(InitinventoryData);
	}
	for (auto& i : tempInventoryItems)
	{
		if ((itemisvaild(i)))
		{
			InventoryData.Add(i);
		}
	}
}

TArray<FItemDatainfo> USD_InventoryComponent::GetInventoryItems()
{
	// 인벤토리구조체 배열을 반환시킴
	return InventoryData;
}

void USD_InventoryComponent::InitInventory(int InventorySize)
{
	// 인벤토리 초기화
	InventoryData.Empty();
	for (int i = 0; i < InventorySize; i++)
	{
		InventoryData.Add(InitinventoryData);
	}
}

void USD_InventoryComponent::ClearInventoryItem(int SlotCount)
{
	// SlotCount에 해당하는 인벤토리 배열을 초기화시킴
	InventoryData[SlotCount] = InitinventoryData;
}

void USD_InventoryComponent::OpenInventory()
{
	//if (InventoryWidget)
	//{
	//	}

}
