// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PotionItemData.h"
#include "../RPGImitationCharacter.h"

UPotionItemData::UPotionItemData()
{
	PotionAmount = 10.f;
}

void UPotionItemData::UseItem(class ARPGImitationCharacter* Character)
{
	Super::UseItem(Character);

	switch (ConsumableType)
	{
	case EConsumableType::CONSUMABLE_HealthPotion:
		Character->DrinkHpPotion(PotionAmount);
		break;

	case EConsumableType::CONSUMABLE_ManaPotion:
		Character->DrinkManaPotion(PotionAmount);
		break;

	case EConsumableType::CONSUMABLE_ExpPotion:
		Character->DrinkExpPotion(PotionAmount);
		break;

	case EConsumableType::CONSUMABLE_None:
		break;
	}
}