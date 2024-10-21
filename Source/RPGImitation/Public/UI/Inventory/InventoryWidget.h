// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	void InitGrid();

	class UItemData* InitItemData();


	void SetCurrentItemArray(int32& Index);

protected:

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* UGP_ItemInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<class UInventoryItemWidget> InventoryItemWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 RowSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 ColSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	class UInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere)
		bool IsPanelCreated = false;

};
