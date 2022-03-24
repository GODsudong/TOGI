// Fill out your copyright notice in the Description page of Project Settings.


#include "SD_InventoryManagerComponent.h"

// Sets default values for this component's properties
USD_InventoryManagerComponent::USD_InventoryManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USD_InventoryManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USD_InventoryManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USD_InventoryManagerComponent::LoadInventroy()
{

}

void USD_InventoryManagerComponent::CreateInventorySlots(int InventroySize, int SlotPerRow)
{
	if (InventroySize > 0)
	{
		
	}
}

void USD_InventoryManagerComponent::AddInventorySlot(int Row, int Colum, int Slot)
{
	int LocalRow = Row;
	int LocalColumn = Colum;
}

void USD_InventoryManagerComponent::ClearInventorySlotItem()
{
}

void USD_InventoryManagerComponent::RefreshInventorySlots()
{
}

void USD_InventoryManagerComponent::GetInventoryItem()
{
}

void USD_InventoryManagerComponent::SetInventorySlotItem()
{
}

void USD_InventoryManagerComponent::IncreaseInventorySlots()
{
}

void USD_InventoryManagerComponent::DecreaseInventorySlots()
{
}

void USD_InventoryManagerComponent::RemoveInventorySlot()
{
}

void USD_InventoryManagerComponent::ClearInventorySlotItems()
{
}

