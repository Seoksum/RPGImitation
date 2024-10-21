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

	void SetMailInfo(class UMailData* InMail);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_Sender;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* T_Title;

	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Item;

	



};
