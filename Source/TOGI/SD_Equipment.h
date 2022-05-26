// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SD_Equipment.generated.h"

/**
 * 
 */
UCLASS()
class TOGI_API USD_Equipment : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel* CanvasPanel;
	UPROPERTY(Meta = (BindWidget))
		class UBorder* FirstBorder;
	UPROPERTY(Meta = (BindWidget))
		class UOverlay* Overlay;
	UPROPERTY(Meta = (BindWidget))
		class UCanVasPanel* EquipCanvasPanel;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* Head;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* Gloves;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* Shoes;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* LeftHand;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* RightHand;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* LeftAccessory;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* RightAccessory;
	UPROPERTY(Meta = (BindWidget))
		class UHorizontalBox* SizeBox;
	UPROPERTY(Meta = (BindWidget))
		class UVerticalBox* FirstVerticalBox;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Health;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Damage;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Defense;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* MovementSpeed;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* MaxStamina;
	UPROPERTY(Meta = (BindWidget))
		class UVerticalBox* SecondVerticalBox;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* RegenStamina;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* CriticalChance;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Cooldown;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* AttackDelay;
	UPROPERTY(Meta = (BindWidget))
		class UBorder* SecondBorder;
	UPROPERTY(Meta = (BindWidget))
		class UHorizontalBox* HorizontalBox;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Equipment;
	UPROPERTY(Meta = (BindWidget))
		class UButton* Button;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* CloseBtn;



};
