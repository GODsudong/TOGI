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
	//itemSlot�� �ε����� �ش��ϴ� �迭�� ������ ������ ��ȯ��
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
	// �κ��丮�� ������� ī�����Ͽ� ��ȯ��
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
	// �κ��丮�� ������ ���� ������ ī�����Ͽ� ��ȯ��
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
	// �κ��丮�� ũ�⸦Amount��ŭ ������Ŵ
	for (int i = 0; i < Amount; i++)
	{
		InventoryData.Add(InitinventoryData);
	}
}

void USD_InventoryComponent::DecreaseInventorySize(int Amount)
{
	// �κ��丮�� ũ�⸦ ���ҽ�Ű�� �Լ�
}

void USD_InventoryComponent::LoadInventoryItems(int InventorySize, FItemDatainfo InventroyItem)
{
	// �κ��丮�� ������ �۵��� �Լ� �κ��丮�� �������� ���ĵ� ����ȴ�
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
	// �κ��丮����ü �迭�� ��ȯ��Ŵ
	return InventoryData;
}

void USD_InventoryComponent::InitInventory(int InventorySize)
{
	// �κ��丮 �ʱ�ȭ
	InventoryData.Empty();
	for (int i = 0; i < InventorySize; i++)
	{
		InventoryData.Add(InitinventoryData);
	}
}

void USD_InventoryComponent::ClearInventoryItem(int SlotCount)
{
	// SlotCount�� �ش��ϴ� �κ��丮 �迭�� �ʱ�ȭ��Ŵ
	InventoryData[SlotCount] = InitinventoryData;
}

void USD_InventoryComponent::OpenInventory()
{
	//if (InventoryWidget)
	//{
	//	}

}
