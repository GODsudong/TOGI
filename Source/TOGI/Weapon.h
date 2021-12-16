// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState :uint8
{
	EWS_Pickup UMETA(DisplayName = "Pickup"),
	EWS_Equpped UMETA(DisplayName = "Equipped"),

	EWS_MAX UMETA(DisplayName = "DefaultMax")
};
UENUM(BlueprintType)
enum class EWeaponType :uint8
{
	EWT_LWeapon UMETA(DisplayName = "LeftWeapon"),
	EWT_RWeapon UMETA(DisplayName = "RightWeapon"),
	EWT_BackWeapon UMETA(DisplayName = "BackWeapon"),
};
/**
 * 
 */
UCLASS()
class TOGI_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = "Item")
	EWeaponState WeaponState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EWeaponType WeaponType;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SkeletalMesh")
		class USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
		class USoundCue* OnEquipSound;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void Equip(class AMyPlayer* Char);

	FORCEINLINE void SetWeaponstate(EWeaponState state) { WeaponState = state; }
	FORCEINLINE EWeaponState GetWeaponstate() { return WeaponState; }
};
