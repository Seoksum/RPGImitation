// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StatComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFrameworks/MyGameModeBase.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "UI/Stat/EnemyStatBarWidget.h"
#include "AI/AIController_Enemy.h"
#include "Enemies/EnemyAnimInstance.h"
#include "GameFrameworks/MyGameModeBase.h"

// Sets default values
AEnemy::AEnemy()
{
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
	GetCapsuleComponent()->BodyInstance.SetCollisionProfileName(FName("Enemy"));
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	// AI Controller »ý¼º
	AIControllerClass = AAIController_Enemy::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Stat = CreateDefaultSubobject<UStatComponent>(TEXT("STAT"));

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 240.f));
	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarUserWidget(TEXT("WidgetBlueprint'/Game/Contents/UI/Stat/WBP_EnemyStatBar.WBP_EnemyStatBar_C'"));
	if (HpBarUserWidget.Succeeded())
	{
		HpBar->SetWidgetClass(HpBarUserWidget.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 50.f));
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	IsAttacking = false;
	IsDeath = false;
	MaxAttackIndex = 3;
	AttackRange = 500.f;
	Level = 1;

	DisplayRange = 1200.0f;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (Stat)
	{
		Stat->SetLevelStat(Level);
		Stat->OnHealthChanged.AddUObject(this, &AEnemy::OnHealthChanged);
	}
}

void AEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AEnemy::OnAttackMontageEnded);
		AnimInstance->EnemyAttackHit.AddUObject(this, &AEnemy::AttackCheck);
	}

	HpBar->InitWidget();
	UEnemyStatBarWidget* EnemyWidget = Cast<UEnemyStatBarWidget>(HpBar->GetUserWidgetObject());
	if (EnemyWidget)
	{
		EnemyWidget->BindHp(Stat);
		EnemyWidget->BindLevel(Level);
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();
		if (PlayerPawn)
		{
			float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
			HpBar->SetHiddenInGame(Distance > DisplayRange);
		}
	}
}

void AEnemy::Attack()
{
	if (IsAttacking || Stat->GetCurrentHp() <= 0.f)
		return;

	IsAttacking = true;
	AnimInstance->PlayAttackMontage();
	AnimInstance->JumpToSection(AttackIndex);
	AttackIndex = (AttackIndex + 1) % MaxAttackIndex;
}

//float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
//{
//	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
//	Stat->OnAttacked(DamageAmount);
//	return DamageAmount;
//}

void AEnemy::OnHealthChanged(float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Health >= 0.1f || IsDeath)
		return;

	IsDeath = true;
	AMyGameModeBase* MyGameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	if (MyGameMode)
	{
		MyGameMode->IncreaseExp(InstigatedBy, EnemyExp);
		MyGameMode->PawnKilled(this);
	}
	//OnDeath_Implementation();
}

void AEnemy::OnDeath_Implementation()
{
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
}

void AEnemy::AttackCheck(float Damage, class UParticleSystem* HitParticleSystem)
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	Params.AddIgnoredActor(this);

	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + GetActorForwardVector() * AttackRange;

	bool bResult = GetWorld()->LineTraceSingleByChannel(OUT HitResult, TraceStart, TraceEnd, ECC_GameTraceChannel1, Params);

	if (bResult)
	{
		FDamageEvent DamageEvent;
		HitResult.Actor->TakeDamage(Damage, DamageEvent, GetController(), this);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticleSystem, HitResult.Actor->GetTransform());
	}

}

void AEnemy::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

UStatComponent* AEnemy::GetStatComponent()
{
	if (nullptr == Stat) { Stat = NewObject<UStatComponent>(); }
	return Stat;
}


