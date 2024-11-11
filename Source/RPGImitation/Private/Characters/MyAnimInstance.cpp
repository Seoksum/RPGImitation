// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/StatComponent.h"
#include "../RPGImitationCharacter.h"


UMyAnimInstance::UMyAnimInstance()
{
	AttackRange = 500.f;
	AttackPower = 30.f;

	WeaponType = EWeaponType::WEAPON_None;
}

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ARPGImitationCharacter* PlayerCharacter = Cast<ARPGImitationCharacter>(TryGetPawnOwner());
	if (PlayerCharacter)
	{
		Stat = PlayerCharacter->GetStatComponent();
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 플레이어 기본 제공 상태
	ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character)
	{
		Speed = Character->GetVelocity().Size();
		Direction = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
		IsFalling = Character->GetMovementComponent()->IsFalling();	
	}


	ARPGImitationCharacter* PlayerCharacter = Cast<ARPGImitationCharacter>(TryGetPawnOwner());
	if (PlayerCharacter)
	{
		WeaponType = PlayerCharacter->GetCurrentWeaponType();
		IsDeath = PlayerCharacter->GetIsPlayerDead();
	}
}

void UMyAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.f);
}

void UMyAnimInstance::PlayAttackMontageQ()
{
	Montage_Play(AttackMontage_Q, 1.f);
}

void UMyAnimInstance::PlayAttackMontageE()
{
	Montage_Play(AttackMontage_E, 1.f);
}

void UMyAnimInstance::PlayAttackMontageR()
{
	Montage_Play(AttackMontage_R, 1.f);
}

void UMyAnimInstance::PlayBowAttackMontage()
{
	Montage_Play(BowAttackMontage, 1.f);
}

void UMyAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AttackMontage);
}

FName UMyAnimInstance::GetAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UMyAnimInstance::AnimNotify_AttackHit()
{
	TraceDistance = AttackRange;
	OnAttackHit.Broadcast(Stat->GetTotalStat().Attack, TraceDistance, EnemyHitParticle);
}

void UMyAnimInstance::AnimNotify_AttackHit_Q()
{

	TraceDistance = AttackRange * 1.2f;
	OnAttackHit_Q.Broadcast(Stat->GetTotalStat().AttackQ, TraceDistance, EnemyHitParticle);
}

void UMyAnimInstance::AnimNotify_AttackHit_E()
{
	TraceDistance = AttackRange * 1.5f;
	OnAttackHit_E.Broadcast(Stat->GetTotalStat().AttackE , TraceDistance, EnemyHitParticle);
}

void UMyAnimInstance::AnimNotify_AttackHit_R()
{
	TraceDistance = AttackRange * 2.f;
	OnAttackHit_R.Broadcast(Stat->GetTotalStat().AttackR , TraceDistance, EnemyHitParticle);

}





