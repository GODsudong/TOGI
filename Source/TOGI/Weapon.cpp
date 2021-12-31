// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"


#include "Components/SkeletalMeshComponent.h"
#include "MyPlayer.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Enemybase.h"
#include "Kismet/GameplayStatics.h"
// #include "EnemyBase.h"

AWeapon::AWeapon()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	WeaponState = EWeaponState::EWS_Pickup;
	WeaponType = EWeaponType::EWT_RWeapon;

	CombatCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CombatCollision->SetupAttachment(GetRootComponent());

	Damage = 25.0f;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CombatCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::CombatOnOverlapBegin);
	CombatCollision->OnComponentEndOverlap.AddDynamic(this, &AWeapon::CombatOnOverlapEnd);

	CombatCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CombatCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CombatCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CombatCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
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
		SetInstigator(Char->GetController());
				
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);		// 타겟 엑터의 채널을 변경시킴
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		SkeletalMesh->SetSimulatePhysics(false);

		CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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
		Char->isEquipped = true;
	}
}

void AWeapon::CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
		if (Enemy)
		{
			if (Enemy->HitParticle)
			{
				const USkeletalMeshSocket* WeaponSoket = SkeletalMesh->GetSocketByName("HitParticleSoket");
				if (WeaponSoket)
				{
					FVector SoketLocation = WeaponSoket->GetSocketLocation(SkeletalMesh);
					// UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Enemy->HitParticle, SoketLocation, FRotator(0.f), false);
				}
			}
			if (Enemy->HitSound)
			{
				UGameplayStatics::PlaySound2D(this, Enemy->HitSound);
			}
			if (DamageTypeClass)
			{
				UE_LOG(LogTemp, Log, TEXT("WeaponHit DamageTypeClass"));
				UGameplayStatics::ApplyDamage(Enemy, Damage, WeaponInstigator, this, DamageTypeClass);
			}
		}
	}
}

void AWeapon::CombatOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AWeapon::ActivateCollision()												// 애니메이션에서 처리
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// UGameplayStatics::PlaySound2D(this, SwingSound);
}

void AWeapon::DeactivateCollision()
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
