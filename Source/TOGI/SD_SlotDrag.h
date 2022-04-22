// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SD_SlotDrag.generated.h"


UENUM(BlueprintType)
enum class ESlotType : uint8
{
	OptionA,
	OptionB
};

/**
 * 
 */
UCLASS()
class TOGI_API USD_SlotDrag : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int FromNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TEnumAsByte<ESlotType> Type;
};
