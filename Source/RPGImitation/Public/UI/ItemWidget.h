// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized();

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;


	
public:

	void SetItemInfo(UItemData* InItem);

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemName;


};
