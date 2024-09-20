// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScrollBoxInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UScrollBoxInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// 아이템을 ScrollBox에 추가하는 함수
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemToInventory(class AItem* InItem);

public:

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ItemScrollBox;


	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<class UItemWidget> ItemWidgetClass;
	


};

