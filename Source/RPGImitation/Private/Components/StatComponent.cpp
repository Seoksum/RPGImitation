// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatComponent.h"
#include "Interfaces/DeathInterface.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentLevel = 1;
}

void UStatComponent::SetLevelStat(int32 NewLevel)
{
	//MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//BaseStat = MyGameInstance->GetCharacterStat(CurrentLevel);
	MaxHp = 200;
	MaxMana = 200;
	SetHp(MaxHp);
	SetMana(MaxHp);
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
	OnManaChanged.Broadcast(CurrentMana, GetMaxMana());
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


