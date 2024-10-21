// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameData/ShopItemDataTable.h"
#include "ShopItemListWidget.generated.h"

/**
 * 
 */


UCLASS()
class RPGIMITATION_API UShopItemListWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	void InitShopListWidget();

	UPROPERTY(EditAnywhere, Category = "Item")
		int32 ItemCount;


public:

	class UItemData* MakeItemData(FShopItemDataTable* ShopItemDataTable);

	UPROPERTY()
	class UShopItemData* ShopItem;

	UPROPERTY(meta = (BindWidget))
	class UListView* ShopListView;

	UPROPERTY(VisibleAnywhere)
	bool IsShopCreated = false;


};
