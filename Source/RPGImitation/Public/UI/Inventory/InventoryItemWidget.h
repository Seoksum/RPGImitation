// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	
public:

	void SetItemInfo(class UItemData* InItem);

	UFUNCTION()
	void OnClickUseItem();


protected:

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_ItemImage;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_ItemButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	class UItemData* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int32 GoldAmount;
	


};
