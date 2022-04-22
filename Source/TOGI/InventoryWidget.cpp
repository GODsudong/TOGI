// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayer.h"
#include "InventoryWidget.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


void UInventoryWidget::GetText()
{

}

float UInventoryWidget::GetPercent()
{
	if (PlayerReference)
	{
		float HP = PlayerReference->HP;
		float Max_HP = PlayerReference->MAX_HP;
		return HP / Max_HP;
	}
	else
	{
		// PlayerReference ���Ҵ� ���۷��� ã�� �κ� �˾ƺ���
	}
	return 0;

}



