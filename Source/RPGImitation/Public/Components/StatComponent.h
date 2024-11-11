// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/StatDataTable.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChanged, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnManaChanged, float);
DECLARE_MULTICAST_DELEGATE_FiveParams(FOnHealthChanged, float, float, const class UDamageType*, class AController*, AActor*);
DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerLevelUp, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStatChanged, const FStatDataTable&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddWeaponAttack, float);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGIMITATION_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

protected:
	
	virtual void BeginPlay() override;



public:

	void SetLevelStat(int32 NewLevel);

	void SetHp(float Hp);

	void SetMana(float Mana);

	void SetExp(int32 Exp);

	void OnAttacked(float DamageAmount);
	void OnAttacking(float ManaAmount);

	void UseHpPotion(float Amount);
	void UseManaPotion(float Amount);

	void SetWeaponStat(const FStatDataTable& NewWeaponStat);

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


public:

	FOnHpChanged OnHpChanged;

	FOnManaChanged OnManaChanged;

	FOnDeath OnDeath;

	FOnPlayerLevelUp OnPlayerLevelUp;

	FOnStatChanged OnStatChanged;

	FOnAddWeaponAttack OnAddWeaponAttack;

	FOnHealthChanged OnHealthChanged;

public:

	FORCEINLINE float GetMaxHp() const { return MaxHp; }
	FORCEINLINE float GetMaxMana() const { return MaxMana; }
	FORCEINLINE float GetHpRatio() const { return (CurrentHp / MaxHp); }

	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	FORCEINLINE float GetCurrentMana() const { return CurrentMana; }

	FORCEINLINE FStatDataTable GetTotalStat() const { return BaseStat + WeaponStat; }




protected:

	UPROPERTY(VisibleInstanceOnly, Category = "Stat")
	float MaxHp;

	UPROPERTY(VisibleInstanceOnly, Category = "Stat")
	float MaxMana;

	UPROPERTY(Transient, EditAnywhere, Category = "Stat")
	float CurrentHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	float CurrentMana;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	float CurrentExp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	float CurrentLevel;
	
	UPROPERTY(EditAnywhere, Category = "Stat")
	float MaxLevel;

	UPROPERTY(EditAnywhere, Category = "State")
	bool bIsDead;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	FStatDataTable BaseStat;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	FStatDataTable WeaponStat;


		
};
