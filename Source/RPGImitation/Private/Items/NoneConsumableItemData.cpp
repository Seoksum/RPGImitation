// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NoneConsumableItemData.h"
#include "../RPGImitationCharacter.h"
#include "GameData/GameEnums.h"

void UNoneConsumableItemData::UseItem(class ARPGImitationCharacter* Character)
{
	Super::UseItem(Character);

	switch (NoneConsumableType)
	{
	case ENoneConsumableType::NONECONSUMABLE_Weapon:
		Character->EquipWeaponItem(ItemName);
		break;
	case ENoneConsumableType::NONECONSUMABLE_Accessory:
		Character->EquipAccessory(ItemName, GetSocketName());
		break;
	default:
		break;
	}
}

FString UNoneConsumableItemData::GetSocketName()
{
	FString SocketName;
	for (int32 i = 0; i < ItemName.Len(); i++)
	{
		if (FChar::IsDigit(ItemName[i]))
			break;
		SocketName += ItemName[i];
	}
	SocketName += "Socket";
	return SocketName;
}
