// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MydataStruct.h" 
#include "SD_InventoryManagerComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 *
 */
UCLASS()
class TOGI_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> HUDOverlayAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		UUserWidget* HUDOverlay;

	FStatusPoint Status;



protected:
	virtual void BeginPlay() override;

public:
	void UpdatePlayerStatus();

};