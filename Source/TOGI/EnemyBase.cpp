
#include "EnemyBase.h"
#include "AIController.h"
#include "MyPlayer.h"
#include "BTAIController.h"
#include "Components/WidgetComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsAttacking = false;

	// AIControllerClass 는 AI에 의해 폰이 제어될 때 사용할 기본 클래스입니다
	AIControllerClass = ABTAIController::StaticClass();

	// AutoPossessAI 는 폰의 생성 시기에 따른 AI 컨트롤러의 소유를 결정합니다 AIControllerClass가 할당되어있을때만 설정 가능
	// Disabled,PlacedInWorld,Spawned,PlacedInWorldOrSpawned 4가지 옵션이 존재
	AutoPossessAI = EAutoPossessAI::PlacedInWorld;

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidget->SetupAttachment(GetMesh());
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/SD_UI/BP_HPBar.BP_HPBar_C"));
	if (UI_HUD.Succeeded())
	{
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<AAIController>(GetController());
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::EnemyDead()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		//죽는 애니메이션 추가해야됨
	}
	SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Dead);

	// 콜라이더 해제
	Destroy();	//테스트용
}



void AEnemyBase::Attack()
{
	UE_LOG(LogTemp, Log, TEXT("EnemyAttack"));
	SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Attacking);
}

void AEnemyBase::OnAttackMontageEnded()
{
	SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Idle);
	OnAttackEnd.Broadcast();
	UE_LOG(LogTemp, Log, TEXT("EnemyAttackEnd"));
}
