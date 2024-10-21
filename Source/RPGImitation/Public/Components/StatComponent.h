// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChanged, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnManaChanged, float, float);
DECLARE_MULTICAST_DELEGATE(FOnDeath);



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

	void OnAttacked(float DamageAmount);
	void OnAttacking(float ManaAmount);

	void UseHpPotion(float Amount);
	void UseManaPotion(float Amount);


public:

	FOnHpChanged OnHpChanged;

	FOnManaChanged OnManaChanged;

	FOnDeath OnDeath;


public:

	FORCEINLINE float GetMaxHp() const { return MaxHp; }
	FORCEINLINE float GetMaxMana() const { return MaxMana; }
	FORCEINLINE float GetHpRatio() const { return (CurrentHp / MaxHp); }

	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	FORCEINLINE float GetCurrentMana() const { return CurrentMana; }

	//FORCEINLINE FCharacterStat GetTotalStat() const { return BaseStat + WeaponStat; }




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
	float CurrentLevel;

	//UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	//FCharacterStat BaseStat;
	//
	//UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = "true"))
	//FCharacterStat WeaponStat;


		
};
