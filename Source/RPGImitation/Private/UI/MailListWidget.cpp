// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MailListWidget.h"
#include "Components/ListView.h"
#include "UI/MailWidget.h"
#include "Items/MailData.h"

void UMailListWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UMailListWidget::AddMailToList(class UMailData* InMailData)
{
	if (!MailListView) return;

	//UMailWidget* NewItemWidget = CreateWidget<UMailWidget>(GetWorld(), MailWidgetClass);
	//if (NewItemWidget)
	//{
	//	NewItemWidget->SetMailInfo(InMailData);
	//	MailListView->AddItem(InMailData);
	//	MailListView->RequestRefresh();
	//}

	UE_LOG(LogTemp, Log, TEXT("UMailListWidget::AddMailToList"));
	UMailData* MailData = NewObject<UMailData>(this);

	MailListView->AddItem(InMailData);
	MailListView->RequestRefresh();
}