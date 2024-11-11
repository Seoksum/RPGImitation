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

	virtual void Tick(float DeltaTime) override;


public:

	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnHealthChanged(float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


	virtual void OnDeath_Implementation();

	virtual void Attack();

	void AttackCheck(float Damage,class UParticleSystem* HitParticleSystem);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	class UStatComponent* GetStatComponent();

protected:

	UPROPERTY(VisibleAnywhere, Category = "AnimInstance")
	class UEnemyAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UWidgetComponent* HpBar;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	class UStatComponent* Stat;

	UPROPERTY(EditAnywhere, Category = "Stat")
	int32 Level;


	UPROPERTY(EditAnywhere, Category = "Stat")
	float AttackRange;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float AttackRadius;

	UPROPERTY(EditAnywhere, Category = "Attack")
	int32 MaxAttackIndex;

	UPROPERTY(EditAnywhere, Category = "Attack")
	int32 AttackIndex = 0;
	
	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool IsAttacking = false;

	UPROPERTY(EditAnywhere, Category = "Stat")
	int32 EnemyExp;

	float DisplayRange;


public:

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool IsDeath = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* DeathSound;

	FOnEnemyDeath OnEnemyDeath;

	FOnAttackEnd OnAttackEnd;

	FTimerHandle DeathTimerHandle;


};
