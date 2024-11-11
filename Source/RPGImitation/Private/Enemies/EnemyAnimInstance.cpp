// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAnimInstance.h"
#include "Enemies/Enemy.h"
#include "Components/StatComponent.h"

UEnemyAnimInstance::UEnemyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Contents/Blueprints/Enemies/AM_EnemyAttack.AM_EnemyAttack'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}

}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AEnemy* OwnerEnemy = Cast<AEnemy>(TryGetPawnOwner());
	if (OwnerEnemy)
	{
		Stat = OwnerEnemy->GetStatComponent();
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	BSNode();
}

void UEnemyAnimInstance::BSNode()
{
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();
		AEnemy* Enemy = Cast<AEnemy>(Pawn);
		if (Enemy)
		{
			SpeedSide = Enemy->GetActorRightVector().Size();
			SpeedForward = Enemy->GetActorForwardVector().Size();
			IsDeath = Enemy->IsDeath;
		}
	}

}

void UEnemyAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.f);
}

void UEnemyAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AttackMontage);
}

FName UEnemyAnimInstance::GetAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UEnemyAnimInstance::AnimNotify_AttackHit()
{
	EnemyAttackHit.Broadcast(Stat->GetTotalStat().Attack, HitParticleSystem);
}

