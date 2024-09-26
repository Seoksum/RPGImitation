// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SendMailListWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API USendMailListWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void AddMailToList(class UMailData* InMailData);

	UFUNCTION(BlueprintCallable)
		void RemoveCheckedMailToList();

	void CheckAllMail(bool IsChecked);


protected:

	UPROPERTY(meta = (BindWidget))
		class UListView* SendMailListView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		TSubclassOf<class USendMailWidget> SendMailWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
		class USendMailWidget* SendMailWidget;
	
};
