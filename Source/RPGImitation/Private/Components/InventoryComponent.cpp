// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Items/ItemData.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	Capacity = 20.f;

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
}

void UInventoryComponent::AddItem(UItemData* Item)
{
	if (ItemArray.Num() >= Capacity || !Item)
		return;

	ItemArray.Add(Item);
	OnInventoryUpdated.Broadcast();
	UE_LOG(LogTemp, Log, TEXT("[%d]Item Name : %s"), ItemArray.Num(), *Item->ItemName);
}

void UInventoryComponent::RemoveItem(UItemData* Item)
{
	if (nullptr == Item)
		return;

	ItemArray.RemoveSingle(Item);
	OnInventoryUpdated.Broadcast();
}

TArray<class UItemData*> UInventoryComponent::GetItemDataArray()
{
	return ItemArray;
}
