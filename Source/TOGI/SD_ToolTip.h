// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SD_ToolTip.generated.h"

/**
 * 
 */
UCLASS()
class TOGI_API USD_ToolTip : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel* ToolTipCanvas;
	UPROPERTY(Meta = (BindWidget))
		class UOverlay* ToolTipOverlay;
	UPROPERTY(Meta = (BindWidget))
		class UImage* ToolTipImage;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* GeneralSizeBox;
	UPROPERTY(Meta = (BindWidget))
		class UVerticalBox* GeneralVerticalBox;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* ItemName;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Quality;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* ItemType;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* MaxHp;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* MaxHpPercent;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Damage;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Defense;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* MovementSpeed;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* MaxStamina;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* RegenStamina;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* CriticalChance;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Cooldown;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* AttackDelay;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Use;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Description;

};
