// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "MydataStruct.h"
#include "SD_GameInstance.generated.h"

UCLASS()
class TOGI_API USD_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USD_GameInstance();

	virtual void Init() override;
	FStatusPoint* GetPlayerData();

private:
	UPROPERTY()
	class UDataTable* Playerstatus;
};
