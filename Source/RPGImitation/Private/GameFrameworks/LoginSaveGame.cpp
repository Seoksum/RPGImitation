// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameworks/LoginSaveGame.h"

ULoginSaveGame::ULoginSaveGame()
{
	ResetData();
}

void ULoginSaveGame::ResetData()
{
	LastRewardTime = FDateTime::Now();
	NextRewardDayButtonIndex = 1;
}
