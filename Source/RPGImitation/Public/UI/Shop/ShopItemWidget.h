// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ShopItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UShopItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION()
	void OnClickPurchaseButton();
	
	void SetItemType();

public:

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_ItemThumbnail;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_ItemName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_ItemDescription;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* T_Price;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Purchase;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		class UShopItemData* ShopItemData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		class UInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		class UItemData* ItemData;

};
