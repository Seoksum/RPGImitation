// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/NoneConsumableItemData.h"
#include "WeaponItemData_Gun.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UWeaponItemData_Gun : public UNoneConsumableItemData
{
	GENERATED_BODY()

public:

	UWeaponItemData_Gun();


	virtual void Attack() override;
	void StartFire();
	void StopFire();

	void PlayFireEffects(FVector TraceEndPoint);
	void PlayImpactEffects(FVector ImpactPoint, UParticleSystem* Particle);



protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<class UDamageType> DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	class UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	class UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	class UParticleSystem* BloodImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	class UParticleSystem* TracerEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UCameraShakeBase> FireCamShake;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float TraceDistance;



public:

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFiredTime;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float RateOfFire; 	// 분 당 발사된 총알 개수

	float TimeBetweenShots;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* FireSound;


};
