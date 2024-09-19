// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Items/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void UInventoryComponent::AddItem(class AItem* Item)
{
	if (ItemArray.Num() >= Capacity || !Item)
		return;

	//Item->OwingInventory = this;
	ItemArray.Add(Item);
	//OnInventoryUpdated.Broadcast(Item);
}

