// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemData.h"
#include "GameData/GameEnums.h"

UItemData::UItemData()
{
	ItemType = EItemType::ITEM_None;

}

void UItemData::UseItem(class ARPGImitationCharacter* Character)
{
	UE_LOG(LogTemp, Log, TEXT("Item Data Uses"));
}