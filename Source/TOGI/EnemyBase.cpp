#include "EnemyBase.h"
#include "Components/SphereComponent.h"
#include "AIController.h"
#include "MyPlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "BTAIController.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsAttacking = false;

	//AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	//AgroSphere->SetupAttachment(GetRootComponent());
	//AgroSphere->InitSphereRadius(600.f);

	//CombatSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CombatSphere"));
	//CombatSphere->SetupAttachment(GetRootComponent());
	//AgroSphere->InitSphereRadius(100.f);


	bOverlappingCombatSphere = false;


	AttackMinTime = 0.5f;
	AttackMaxTime = 3.5f;

	// AIControllerClass 는 AI에 의해 폰이 제어될 때 사용할 기본 클래스입니다
	AIControllerClass = ABTAIController::StaticClass();

	// AutoPossessAI 는 폰의 생성 시기에 따른 AI 컨트롤러의 소유를 결정합니다 AIControllerClass가 할당되어있을때만 설정 가능
	// Disabled,PlacedInWorld,Spawned,PlacedInWorldOrSpawned 4가지 옵션이 존재
	AutoPossessAI = EAutoPossessAI::PlacedInWorld;

} 

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<AAIController>(GetController());

	//AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::AgroSphereOnOverlapBegin);
	//AgroSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::AgroSphereOnOverlapEnd);

	//CombatSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::CombatSphereOnOverlapBegin);
	//CombatSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::CombatSphereOnOverlapEnd);
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



/*BehaviorTree 적용 이전의 AI 추적 코드입니다 이후 충돌 처리는 behaviorTree를 활용해서 처리하게됩니다 20220509 */

//void AEnemyBase::AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (OtherActor)
//	{
//		AMyPlayer* Player = Cast<AMyPlayer>(OtherActor);
//		if (Player)
//		{
//			MoveToTarget(Player);
//		}
//	}
//}
//
//void AEnemyBase::AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	if (OtherActor)
//	{
//		AMyPlayer* Player = Cast<AMyPlayer>(OtherActor);
//		{
//			if (Player)
//			{
//				SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Idle);
//				if (AIController)
//				{
//					AIController->StopMovement();
//				}
//			}
//		}
//	}  
//}
//
//void AEnemyBase::CombatSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (OtherActor)
//	{
//		AMyPlayer* Player = Cast<AMyPlayer>(OtherActor);
//		{
//			if (Player)
//			{
//				Player->SetCombatTarget(this);
//				CombatTarget = Player;
//				bOverlappingCombatSphere = true;
//				SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Attacking);
//				UE_LOG(LogTemp, Log, TEXT("CombatSphereonOverlapBegin"));
//				
//				if (DamageTypeClass)
//				{
//					UGameplayStatics::ApplyDamage(Player, Damage, AIController, this, DamageTypeClass);
//				}
//			}
//		}
//	}
//}
// 
//void AEnemyBase::CombatSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	if (OtherActor)
//	{
//		AMyPlayer* Player = Cast<AMyPlayer>(OtherActor);
//		{
//			if (Player)
//			{
//				if (Player->CombatTarget == this)
//				{
//					Player->SetCombatTarget(nullptr);
//				}
//				bOverlappingCombatSphere = false;
//				if (Enemymovemonetstatus == EEnemyMovementStatus::EMS_Attacking)
//				{
//					MoveToTarget(Player);
//					CombatTarget = nullptr;
//				}
//			}
//		}
//	}
//}

//void AEnemyBase::MoveToTarget(class AMyPlayer* Target)
//{
//	SetEnemyMovementStatus(EEnemyMovementStatus::EMS_MoveToTarget);
//
//	if (AIController)
//	{
//		FAIMoveRequest MoveRequest;
//		MoveRequest.SetGoalActor(Target);
//		MoveRequest.SetAcceptanceRadius(10.0f);
//
//		FNavPathSharedPtr NavPath;
//
//		AIController->MoveTo(MoveRequest, &NavPath);
//
//		auto PathPoints = NavPath->GetPathPoints();
//		for (auto Point : PathPoints)
//		{
//			FVector Location = Point.Location;
//
//			UKismetSystemLibrary::DrawDebugSphere(this, Location, 25.0f, 8, FLinearColor::Red, 5.f, 2.5f);
//
//		}
//	}
//}

float AEnemyBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Log, TEXT("EnemyTakeDamage"));
	if (Hp - DamageAmount <= 0.f)
	{
		Hp -= DamageAmount;
		EnemyDead();
	}
	else
	{
		Hp -= DamageAmount;
	}

	return DamageAmount;
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
	// OnAttackEnd.BroadCast() 애니메이션 몽타주가 끝나는 지점으로 이동해줘야함
	OnAttackEnd.Broadcast();
	UE_LOG(LogTemp, Log, TEXT("EnemyAttackEnd"));
}

void AEnemyBase::OnAttackMontageEnded()
{
	SetEnemyMovementStatus(EEnemyMovementStatus::EMS_Idle);
	OnAttackEnd.Broadcast();
	UE_LOG(LogTemp, Log, TEXT("EnemyAttackEnd"));
}