// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PotionItemData.h"
#include "../RPGImitationCharacter.h"

UPotionItemData::UPotionItemData()
{

}

void UPotionItemData::UseItem(class ARPGImitationCharacter* Character)
{
	Super::UseItem(Character);

	switch (ConsumableType)
	{
	case EConsumableType::CONSUMABLE_HealthPotion:
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Drink Hp Potion")));
		break;

	case EConsumableType::CONSUMABLE_ManaPotion:
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FString(TEXT("Drink Mana Potion")));
		break;

	case EConsumableType::CONSUMABLE_ExpPotion:
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString(TEXT("Drink Exp Potion")));
		break;

	case EConsumableType::CONSUMABLE_None:
		break;
	}
}