// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

UCLASS()
class RPGIMITATION_API AArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrow();

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedcComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetArrowSpeed(float ArrowSpeedVal);


public:

	UPROPERTY(EditAnywhere, Category = "Component")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* DefaultEffect;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* SkillEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	float InitialValue;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BaseDamage;

};
