 // Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h" 
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bLMBDown = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	FollowCamera->bUsePawnControlRotation = false;

	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;

	ComboCount = -1;	
	AttackDelay = 0.8f;
	bAttacking = false;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Log, TEXT("%f"),AttackDelay);
	UE_LOG(LogTemp, Log, TEXT("%d"), ComboCount);
	AttackDelay -= DeltaTime;
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayer::MoveRight);

	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMyPlayer::LMBDown);
	PlayerInputComponent->BindAction("LMB", IE_Released, this, &AMyPlayer::LMBUp);
	


	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMyPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMyPlayer::LookUpAtRate);

}

void AMyPlayer::MoveForward(float value)
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}


void AMyPlayer::MoveRight(float value)
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void AMyPlayer::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate*GetWorld()->GetDeltaSeconds());
}

void AMyPlayer::LookUpAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMyPlayer::LMBDown()
{
	bLMBDown = true;
	Attack();

	// 클릭으로 아이템 작창
	//if (ActiveOverlappingItem)
	//{
	//	AWeapon* weapon = Cast<AWeapon>(ActiveOverlappingItem);
	//	if (weapon)
	//	{
	//		weapon->Equip(this); 
	//		SetActiveoverlappingItem(nullptr);
	//	}
	//}
}

void AMyPlayer::LMBUp()
{
	bLMBDown = false;	
}

void AMyPlayer::Attack()
{
	if (!bAttacking)
	{
		bAttacking = true;

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && CombatMontage)
		{
			if (AttackDelay >= 0 && ComboCount != 2)
			{
			}
			else
			{
				ComboCount = -1;
			}
			ComboCount++;
			AttackDelay = 0.8f;
			switch (ComboCount)
			{
			case 0:
				AnimInstance->Montage_Play(CombatMontage, 1.0f);
				AnimInstance->Montage_JumpToSection(FName("Slash_1"), CombatMontage);
				break;
			case 1:
				AnimInstance->Montage_Play(CombatMontage, 1.0f);
				AnimInstance->Montage_JumpToSection(FName("Slash_2"), CombatMontage);
				break;
			case 2:
				AnimInstance->Montage_Play(CombatMontage, 1.0f);
				AnimInstance->Montage_JumpToSection(FName("Slash_3"), CombatMontage);
				break;

			default:
				break;
			}
		}
	}
}

void AMyPlayer::AttackEnd()
{
	bAttacking = false;
	if (bLMBDown)
	{
		Attack();
	}
}