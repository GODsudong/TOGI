// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SD_DraggedItem.generated.h"

/**
 * 
 */
UCLASS()
class TOGI_API USD_DraggedItem : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel* DraggedItemCanvasPanel;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* IconSizeBox;
	UPROPERTY(Meta = (BindWidget))
		class UImage* Icon;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* AmountTextSizeBox;
	UPROPERTY(Meta = (BindWidget))
		class UBorder* AmountBorder;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Amount;
};
