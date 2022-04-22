// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SD_Inventory_Slot.generated.h"

/**
 * 
 */
UCLASS()
class TOGI_API USD_Inventory_Slot : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override; // 생성자 뷰포트에 올려둘때 호출


	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel* CanvasPanel;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* SizeBox;
	UPROPERTY(Meta = (BindWidget))
		class UOverlay* Overlay;
	UPROPERTY(Meta = (BindWidget))
		class UBorder* SlotBorder;
	UPROPERTY(Meta = (BindWidget))
		class UButton* Button;
	UPROPERTY(Meta = (BindWidget))
		class UBorder* ItemBorder;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Amount;

	void OnClickSlot();
	// FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

};
