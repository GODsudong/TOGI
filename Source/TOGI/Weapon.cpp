// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "MyPlayer.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

AWeapon::AWeapon()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	WeaponState = EWeaponState::EWS_Pickup;
	WeaponType = EWeaponType::EWT_RWeapon;
}



void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if ((WeaponState == EWeaponState::EWS_Pickup)&&OtherActor)
	{
		AMyPlayer* Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			Equip(Player);
			//UE_LOG(LogTemp, Log, TEXT("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"));
			Player->SetActiveoverlappingItem(this);

			//Destroy();
		}
	}
}


void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	if (OtherActor)
	{
		AMyPlayer* Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			Player->SetActiveoverlappingItem(nullptr);

		}
	}

}

void AWeapon::Equip(AMyPlayer* Char)
{
	if (Char)
	{
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);		// Å¸°Ù ¿¢ÅÍÀÇ Ã¤³ÎÀ» º¯°æ½ÃÅ´
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		SkeletalMesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* Soket = Char->GetMesh()->GetSocketByName("hand_lSocket");;
		switch (WeaponType)
		{
		case EWeaponType::EWT_LWeapon:
			Soket = Char->GetMesh()->GetSocketByName("hand_lSocket");
			break;
		case EWeaponType::EWT_RWeapon:
			Soket = Char->GetMesh()->GetSocketByName("hand_rSocket");
			break;
		case EWeaponType::EWT_BackWeapon:
			Soket = Char->GetMesh()->GetSocketByName("Backpack");
			break;
		}
		if (Soket)
		{
			Soket->AttachActor(this, Char->GetMesh());
			bRotate = false;
			Char->SetEquippedWeapon(this);
			Char->SetActiveoverlappingItem(nullptr);
		}
		if (OnEquipSound) UGameplayStatics::PlaySound2D(this, OnEquipSound);
	}
}

