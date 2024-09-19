// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdated, class AItem*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGIMITATION_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32 Capacity;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<class AItem*> ItemArray;


public:

	void AddItem(class AItem* Item);
		

public:

	FOnInventoryUpdated OnInventoryUpdated;
};
