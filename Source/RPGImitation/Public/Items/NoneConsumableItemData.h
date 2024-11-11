// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemData.h"
#include "GameData/GameEnums.h"
#include "GameData/StatDataTable.h"
#include "NoneConsumableItemData.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UNoneConsumableItemData : public UItemData
{
	GENERATED_BODY()
	
public:

	void InitializeWorld(UWorld* InWorld);

	void SetOwner(class ARPGImitationCharacter* InOwner);

	virtual void UseItem(class ARPGImitationCharacter* Character) override;

	virtual void Attack();

	virtual void Attack(int32 damage, float TraceDistance, class UParticleSystem* Particle);


	FString GetSocketName();

	FStatDataTable GetWeaponStat();

protected:

	UPROPERTY(VisibleAnywhere)
	class UWorld* World;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ARPGImitationCharacter* MyOwner;

	UPROPERTY(EditAnywhere, Category = "Stat")
	FStatDataTable WeaponStat;
	
	EWeaponType WeaponType;


};
