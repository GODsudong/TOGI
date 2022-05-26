// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "SD_HPBar.h"

void USD_HPBar::NativeConstruct()
{
	Super::NativeConstruct();
}

float USD_HPBar::GetText()
{
	return 0;
}

float USD_HPBar::GetPercent()
{
	if (PlayerReference)
	{
		float HP = PlayerReference->HP;
		float Max_HP = PlayerReference->MAX_HP;
		return HP / Max_HP;
	}
	else
	{
		// PlayerReference 재할당 래퍼런스 찾는 부분 알아보기
	}
	return 0;

}