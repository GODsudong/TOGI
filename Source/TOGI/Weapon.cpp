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
}



void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor)
	{
		AMyPlayer* Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			//Equip(Player);
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

		const USkeletalMeshSocket* RightHandSoket = Char->GetMesh()->GetSocketByName("hand_lSocket");
		if (RightHandSoket)
		{
			UE_LOG(LogTemp, Log, TEXT("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"));
			RightHandSoket->AttachActor(this, Char->GetMesh());
			bRotate = false;
			Char->SetquippedWeapon(this);
		}
		if (OnEquipSound) UGameplayStatics::PlaySound2D(this,OnEquipSound);
	}
}