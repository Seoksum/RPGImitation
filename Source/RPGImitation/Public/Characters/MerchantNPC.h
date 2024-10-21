// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MerchantNPC.generated.h"

UCLASS()
class RPGIMITATION_API AMerchantNPC : public AActor
{
	GENERATED_BODY()
	
public:	

	AMerchantNPC();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnPlayerEnterConversationRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnPlayerExitConversationRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UWidgetComponent* ConversationWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USkeletalMeshComponent* SkeletalMeshComponent;


};
