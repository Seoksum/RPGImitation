// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemList.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UItemList : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	//virtual void NativeOnInitialized();

	virtual void NativeConstruct() override;


public:

	UPROPERTY(meta = (BindWidget))
	class UListView* NearbyItemList;

	void RefreshListView();

	//UFUNCTION(BlueprintCallable)
	void AddItemToList(class AItem* InItem);



protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UItemWidget> ItemWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	class UItemWidget* ItemWidget;


};
