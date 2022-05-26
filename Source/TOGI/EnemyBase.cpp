
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

	// AIControllerClass �� AI�� ���� ���� ����� �� ����� �⺻ Ŭ�����Դϴ�
	AIControllerClass = ABTAIController::StaticClass();

	// AutoPossessAI �� ���� ���� �ñ⿡ ���� AI ��Ʈ�ѷ��� ������ �����մϴ� AIControllerClass�� �Ҵ�Ǿ��������� ���� ����
	// Disabled,PlacedInWorld,Spawned,PlacedInWorldOrSpawned 4���� �ɼ��� ����
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
		//�״� �ִϸ��̼� �߰��ؾߵ�
	}
	SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Dead);

	// �ݶ��̴� ����
	Destroy();	//�׽�Ʈ��
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
