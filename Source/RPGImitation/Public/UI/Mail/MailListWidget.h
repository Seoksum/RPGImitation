// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MailListWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UMailListWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void AddMailToList(class UMailData* InMailData);
	void RemoveMailToList(class UMailData* InMailData);

	UFUNCTION(BlueprintCallable)
	void RemoveCheckedMailToList();

	void CheckAllMail(bool IsChecked);


	UFUNCTION(BlueprintCallable)
	bool CanDeleteReceivedMail();

protected:

	UPROPERTY(meta = (BindWidget))
	class UListView* MailListView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UMailWidget> MailWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	class UMailWidget* MailWidget;


};
