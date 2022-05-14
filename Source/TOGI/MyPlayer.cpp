 // Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/Gameplaystatics.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon.h"
#include "Sound/SoundCue.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnemyBase.h"

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

	DirVec = FVector(0, 0, 0);

	MAX_HP = 10;
	HP = 10;
	isEquipped = false;

	InterpSpeed = 15.0f;
	bInterpToEnemy = false;

	SpeedMagnification = 1.f;
	WKeyInputDelay = 0.f;
	isRun = false;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (CurveFloat)
	{
		FOnTimelineFloat DashCurveCallBack;
		
		FOnTimelineEventStatic DashTimeLineFinishCallBack;

		DashCurveCallBack.BindUFunction(this, FName("DashTimeline"));
		CurveTimeline.AddInterpFloat(CurveFloat, DashCurveCallBack);

		DashTimeLineFinishCallBack.BindUFunction(this, FName("DashFinish"));		// DashFinish 함수 콜백 함수에 바인딩
		CurveTimeline.SetTimelineFinishedFunc(DashTimeLineFinishCallBack);			// TimeLine이 끝날때 호출될 CallBack 함수 추가
	}
}

void AMyPlayer::DashFinish()
{
	isDash = false;
}

void AMyPlayer::DashTimeline(float Value)
{
	AddActorLocalOffset(DirVec*Value*10);
	UE_LOG(LogTemp, Log, TEXT("AMyPlayer::DashTimeline SpeedValue : %f"),Value);
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);
	AttackDelay -= DeltaTime;
	WKeyInputDelay -= DeltaTime;
	if (10<Vital)
	{
		Vital += DeltaTime;
	}
	// UE_LOG(LogTemp, Log, TEXT("%f"),AttackDelay);
	// UE_LOG(LogTemp, Log, TEXT("%d"), ComboCount);


	if (bInterpToEnemy && CombatTarget)			//자동 방향 조절
	{
		FRotator LookAtYaw = GetLookAtRotationYaw(CombatTarget->GetActorLocation());
		FRotator interpRotation = FMath::RInterpTo(GetActorRotation(), LookAtYaw, DeltaTime, InterpSpeed);
		SetActorRotation(interpRotation);
	}
}

void AMyPlayer::WKeyDown()
{
	UE_LOG(LogTemp, Log, TEXT("WKeyDown"));
	if (WKeyInputDelay >= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Run"));
		isRun = true;
		SpeedMagnification = 20.f;
	}
	WKeyInputDelay = 0.2f;
}

void AMyPlayer::WKeyUp()
{
	UE_LOG(LogTemp, Log, TEXT("WKeyUp"));
	isRun = false;
	SpeedMagnification = 1.f;
}

FRotator AMyPlayer::GetLookAtRotationYaw(FVector Target)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target);
	FRotator LookAtRotationYaw(0.f, LookAtRotation.Yaw,0.f);
	return LookAtRotationYaw;
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
	
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMyPlayer::Dashing);

	PlayerInputComponent->BindAction("WKey", IE_Pressed, this, &AMyPlayer::WKeyDown);
	PlayerInputComponent->BindAction("WKey", IE_Released, this, &AMyPlayer::WKeyUp);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMyPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMyPlayer::LookUpAtRate);

	PlayerInputComponent->BindAxis("ZoomIO", this, &AMyPlayer::ZoomInOut);
}

void AMyPlayer::MoveForward(float value)
{
	if ((Controller != nullptr) && (value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		if (isRun)
		{
			AddActorLocalOffset(Direction * value * SpeedMagnification);
		}
		else
		{
			AddMovementInput(Direction * SpeedMagnification, value);
		}
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
	UE_LOG(LogTemp, Log, TEXT("LMBDOWN"));
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



void AMyPlayer::ZoomInOut(float WheelUpDown)
{
	if (0 < -(WheelUpDown))
	{
		if (CameraBoom->TargetArmLength < 600.f)
		{
			CameraBoom->TargetArmLength += -(WheelUpDown) * 10;
		}
	}
	else
	{
		if (200.f < CameraBoom->TargetArmLength)
		{
			CameraBoom->TargetArmLength += -(WheelUpDown) * 10;
		}
	}
}


void AMyPlayer::LMBUp()
{
	bLMBDown = false;	
}

void AMyPlayer::Attack()
{
	UE_LOG(LogTemp, Log, TEXT("Attack"), ComboCount);
	if (isEquipped)
	{
		if (!bAttacking)
		{
			UE_LOG(LogTemp, Log, TEXT("bAttacking = false"), ComboCount);
			bAttacking = true;
			SetInterpToEnemy(true);
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
					UE_LOG(LogTemp, Log, TEXT("Combo1"));
					AnimInstance->Montage_Play(CombatMontage, 1.0f);
					AnimInstance->Montage_JumpToSection(FName("Slash_1"), CombatMontage);
					break;
				case 1:
					UE_LOG(LogTemp, Log, TEXT("Combo2"));
					AnimInstance->Montage_Play(CombatMontage, 1.0f);
					AnimInstance->Montage_JumpToSection(FName("Slash_2"), CombatMontage);
					break;
				case 2:
					UE_LOG(LogTemp, Log, TEXT("Combo3"));
					AnimInstance->Montage_Play(CombatMontage, 1.0f);
					AnimInstance->Montage_JumpToSection(FName("Slash_3"), CombatMontage);
					break;

				default:
					break;
				}
			}
			if (EquippedWeapon->SwingSound)
			{
				UGameplayStatics::PlaySound2D(this, EquippedWeapon->SwingSound);
			}
		}
	}
}

void AMyPlayer::AttackEnd()
{
	UE_LOG(LogTemp, Log, TEXT("AttackEnd = %d"), ComboCount);
	bAttacking = false;
	SetInterpToEnemy(false);
	if (bLMBDown)
	{
		Attack();
	}
}


void AMyPlayer::SetInterpToEnemy(bool Interp)
{
	bInterpToEnemy = Interp;
}


void AMyPlayer::DecrementHealth(float Amount)
{
	HP -= Amount;
}


float AMyPlayer::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	DecrementHealth(DamageAmount);
	return DamageAmount;
}


void AMyPlayer::Dashing() 
{
	if (!(isDash))
	{
		UE_LOG(LogTemp, Log, TEXT("DASH"));
		isDash = true;
		DirVec = FVector(0, 0, 0);
		DirVec.Y = GetInputAxisValue(FName("MoveRight"));
		DirVec.X = GetInputAxisValue(FName("MoveForward"));
		DirVec.Normalize();
		CurveTimeline.PlayFromStart();
		//LaunchCharacter(result * 5000, true, false);
		UE_LOG(LogTemp, Log, TEXT("%s"), *DirVec.ToString());
	}
}
