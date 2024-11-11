// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatComponent.h"
#include "Interfaces/DeathInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "GameFrameworks/MyGameInstance.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UStatComponent::TakeDamage);
	}

	MaxLevel =6;
	CurrentLevel = 1;
}

void UStatComponent::SetLevelStat(int32 NewLevel)
{
	CurrentLevel = FMath::Clamp<float>(NewLevel, 1, MaxLevel);
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BaseStat = MyGameInstance->GetCharacterStat(CurrentLevel);
	MaxHp = BaseStat.MaxHp;
	MaxMana = BaseStat.MaxMana;
	SetHp(MaxHp);
	SetMana(MaxHp);
	OnStatChanged.Broadcast(GetTotalStat());
}

void UStatComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (bIsDead) return;

	CurrentHp = FMath::Clamp(CurrentHp - Damage, 0.0f, MaxHp);
	bIsDead = CurrentHp <= 0.f;
	SetHp(CurrentHp);
	OnHealthChanged.Broadcast(CurrentHp, Damage, DamageType, InstigatedBy, DamageCauser);
}

void UStatComponent::SetHp(float Hp)
{
	CurrentHp = FMath::Clamp<float>(Hp, 0.f, MaxHp);
	if (CurrentHp <= 0)
	{
		CurrentHp = 0;
		if (GetOwner()->Implements<UDeathInterface>())
		{
			IDeathInterface::Execute_OnDeath(GetOwner());
		}
	}
	OnHpChanged.Broadcast(CurrentHp);

}

void UStatComponent::SetMana(float Mana)
{
	CurrentMana = FMath::Clamp(Mana, 0.f, MaxMana);
	OnManaChanged.Broadcast(CurrentMana);
}

void UStatComponent::SetExp(int32 Exp)
{
	CurrentExp += Exp;
	float LevelExp = BaseStat.Exp;
	if (LevelExp <= CurrentExp)
	{
		CurrentLevel = FMath::Clamp<int32>(CurrentLevel + 1, 1, MaxLevel);
		OnPlayerLevelUp.Broadcast(static_cast<int32>(CurrentLevel));
		CurrentExp -= LevelExp;
	}

}
void UStatComponent::OnAttacked(float DamageAmount)
{
	SetHp(CurrentHp - DamageAmount);
}

void UStatComponent::OnAttacking(float ManaAmount)
{
	SetMana(CurrentMana - ManaAmount);
}

void UStatComponent::UseHpPotion(float Amount)
{
	SetHp(CurrentHp + Amount);
}

void UStatComponent::UseManaPotion(float Amount)
{
	SetMana(CurrentMana + Amount);
}

void UStatComponent::SetWeaponStat(const FStatDataTable& NewWeaponStat)
{
	WeaponStat = NewWeaponStat;
	OnAddWeaponAttack.Broadcast(WeaponStat.Attack);
}

