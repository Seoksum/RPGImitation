// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttackHit, float, float, class UParticleSystem*);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttackHit_Q, float, float, class UParticleSystem*);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttackHit_E, float, float, class UParticleSystem*);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttackHit_R, float, float, class UParticleSystem*);


UCLASS()
class RPGIMITATION_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UMyAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	// Play Montage
public:

	void PlayAttackMontage();
	void PlayAttackMontageQ();
	void PlayAttackMontageE();
	void PlayAttackMontageR();


	void JumpToSection(int32 SectionIndex);
	FName GetAttackMontageName(int32 SectionIndex);


	// AnimNotify
private:

	UFUNCTION()
	void AnimNotify_AttackHit();

	UFUNCTION()
	void AnimNotify_AttackHit_Q();

	UFUNCTION()
	void AnimNotify_AttackHit_E();

	UFUNCTION()
	void AnimNotify_AttackHit_R();



	// Player State
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
		float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
		bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
		bool IsDeath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
		float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State", Meta = (AllowPrivateAccess = true))
		float AttackPower;

	// Anim Montage
protected:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage_Q;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage_E;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Montage", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage_R;



	// Particle System
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParticleSystem")
	class UParticleSystem* AttackParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParticleSystem")
	class UParticleSystem* AttackParticleQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ParticleSystem")
	class UParticleSystem* AttackParticleE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class UStatComponent* Stat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float TraceDistance;


	// Delegate
public:

	FOnAttackHit OnAttackHit;
	FOnAttackHit_Q OnAttackHit_Q;
	FOnAttackHit_E OnAttackHit_E;
	FOnAttackHit_R OnAttackHit_R;
};
