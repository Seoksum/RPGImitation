// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddInventoryUpdated,class UItemData*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPGIMITATION_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UInventoryComponent();

	virtual void BeginPlay() override;

	void AddItem(class UItemData* Item);

	void RemoveItem(class UItemData* Item);

	FORCEINLINE TArray<class UItemData*> GetDefaultItems() { return DefaultItems; }
	TArray<class UItemData*> GetItemDataArray();


private:

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		int32 Capacity;

	UPROPERTY(EditDefaultsOnly, Instanced)
		TArray<class UItemData*> DefaultItems;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
		TArray<class UItemData*> ItemArray;

public:

	FOnInventoryUpdated OnInventoryUpdated;
	FOnAddInventoryUpdated OnAddInventoryUpdated;

		
};
