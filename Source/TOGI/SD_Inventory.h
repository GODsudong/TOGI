// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SD_Inventory.generated.h"

/**
 * 
 */
UCLASS()
class TOGI_API USD_Inventory : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// virtual void NativeConstruct() override; // 생성자 뷰포트에 올려둘때 호출

	UPROPERTY(Meta = (BindWidget))
		class UCanvasPanel* InventroyCanvasPanel;
	UPROPERTY(Meta = (BindWidget))
		class UBorder* GeneralBorder;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* GeneralSizeBox;
	UPROPERTY(Meta = (BindWidget))
		class UVerticalBox* VirticalBox;
	UPROPERTY(Meta = (BinWidget))
		class UBorder* WindowHandleBorder;
	UPROPERTY(Meta = (BindWidget))
		class UHorizontalBox* InventoryHorizontalBox;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* InventoryText;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* CloseBtnSizeBox;
	UPROPERTY(Meta = (BindWidget))
		class UButton* CloseBtn;
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* CloseBtnText;
	UPROPERTY(Meta = (BindWidget))
		class USpacer* InventorySpacer;
	UPROPERTY(Meta = (BindWidget))
		class USizeBox* InventroySizeBox;
	UPROPERTY(Meta = (BindWidget))
		class UUniformGridPanel* InventoryGridPanel;



public:
	void OnCloseBtn();

};
