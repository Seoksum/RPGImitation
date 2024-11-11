// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */



DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEnemyAttackHit, float, class UParticleSystem*);

UCLASS()
class RPGIMITATION_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UEnemyAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void BSNode();

	void PlayAttackMontage();

	void JumpToSection(int32 SectionIndex);
	FName GetAttackMontageName(int32 SectionIndex);

private:

	UFUNCTION()
	void AnimNotify_AttackHit();



protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float SpeedSide;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	float SpeedForward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool IsDeath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	class UStatComponent* Stat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		class UParticleSystem* HitParticleSystem;


public:

	FOnEnemyAttackHit EnemyAttackHit;

	
};
