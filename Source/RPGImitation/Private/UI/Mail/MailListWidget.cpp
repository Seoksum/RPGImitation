// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mail/MailListWidget.h"
#include "Components/ListView.h"
#include "Components/CheckBox.h"
#include "UI/Mail/MailWidget.h"
#include "Items/MailData.h"

void UMailListWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UMailListWidget::AddMailToList(class UMailData* InMailData)
{
	if (!MailListView) return;

	InMailData->OwningMailListWidget = this;
	MailListView->AddItem(InMailData);
	MailListView->RequestRefresh();
}

void UMailListWidget::RemoveMailToList(class UMailData* InMailData)
{
	if (!MailListView) return;

	MailListView->RemoveItem(InMailData);
	MailListView->RequestRefresh();
}

void UMailListWidget::RemoveCheckedMailToList()
{
	//TArray<UUserWidget*> DisplayedWidgets = MailListView->GetDisplayedEntryWidgets();
	//for (UUserWidget* Widget : DisplayedWidgets)
	//{
	//    UMailWidget* MyMailWidget = Cast<UMailWidget>(Widget);
	//    if (MyMailWidget && MyMailWidget->CB_MailSelected && MyMailWidget->CB_MailSelected->IsChecked())
	//    {
	//        // 체크된 항목을 ListView에서 제거
	//        MailListView->RemoveItem(MyMailWidget->GetListItem());
	//        MyMailWidget->CB_MailSelected->SetIsChecked(false);
	//        //MailListView->RequestRefresh();
	//    }
	//}

	TArray<UObject*> AllItems = MailListView->GetListItems();
	for (UObject* Item : AllItems)
	{
		UMailData* MyMailWidget = Cast<UMailData>(Item);
		MailListView->RemoveItem(MyMailWidget);
	}

}

void UMailListWidget::CheckAllMail(bool IsChecked)
{
	//TArray<UUserWidget*> DisplayedWidgets = MailListView->GetDisplayedEntryWidgets();
	//for (UUserWidget* Widget : DisplayedWidgets)
	//{
	//    UMailWidget* MyMailWidget = Cast<UMailWidget>(Widget);
	//    MyMailWidget->CB_MailSelected->SetIsChecked(IsChecked);
	//}

	TArray<UObject*> AllItems = MailListView->GetListItems();
	for (UObject* Item : AllItems)
	{
		UMailWidget* InMailWidget = Cast<UMailWidget>(MailListView->GetEntryWidgetFromItem(Item));
		if (InMailWidget && InMailWidget->CB_MailSelected)
		{
			InMailWidget->CB_MailSelected->SetIsChecked(IsChecked);  // 체크박스를 체크 상태로 설정
		}
	}
}

bool UMailListWidget::CanDeleteReceivedMail()
{
	TArray<UUserWidget*> DisplayedWidgets = MailListView->GetDisplayedEntryWidgets();

	for (UUserWidget* Widget : DisplayedWidgets)
	{
		UMailWidget* MyMailWidget = Cast<UMailWidget>(Widget);
		if (MyMailWidget && MyMailWidget->CB_MailSelected && MyMailWidget->CB_MailSelected->IsChecked())
		{
			return true;
		}
	}
	return false;
}
