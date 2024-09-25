// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReceivePostalWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UReceivePostalWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	
public:

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* T_Title;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* T_Sender;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* T_Message;

	void SetMail(class UMailData* Mail);

};
