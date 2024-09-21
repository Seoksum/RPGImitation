// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "MailWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UMailWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;


public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextFrom;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextContents;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextDay;



};
