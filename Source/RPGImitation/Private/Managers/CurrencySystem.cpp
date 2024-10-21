// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/CurrencySystem.h"

UCurrencySystem::UCurrencySystem()
{

}

void UCurrencySystem::AddGold(int32 Amount)
{
	Gold += Amount;
	OnGoldChanged.Broadcast(Gold);
}

bool UCurrencySystem::RemoveGold(int32 Amount)
{
	if (Gold >= Amount)
	{
		Gold -= Amount;
		OnGoldChanged.Broadcast(Gold);
		return true;
	}
	return false;
}