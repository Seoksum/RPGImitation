// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/DeathInterface.h"
#include "Enemy.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemyDeath, int32);
DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);

UCLASS()
class RPGIMITATION_API AEnemy : public ACharacter, public IDeathInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void OnDeath_Implementation();

	virtual void Attack();

	void AttackCheck();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);


protected:

	UPROPERTY(VisibleAnywhere, Category = "AnimInstance")
	class UEnemyAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UWidgetComponent* HpBar;

	UPROPERTY(EditAnywhere, Category = "Stat")
	int32 Level;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float AttackPower;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float AttackRange;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float AttackRadius;

	UPROPERTY(EditAnywhere, Category = "Attack")
	int32 MaxAttackIndex;

	UPROPERTY(EditAnywhere, Category = "Attack")
	int32 AttackIndex = 0;


public:

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	class UStatComponent* Stat;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool IsDeath = false;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool IsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* DeathSound;

	FOnEnemyDeath OnEnemyDeath;

	FOnAttackEnd OnAttackEnd;

	FTimerHandle DeathTimerHandle;


};
