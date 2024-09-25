// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MailListWidget.h"
#include "Components/ListView.h"
#include "Components/CheckBox.h"
#include "UI/MailWidget.h"
#include "Items/MailData.h"

void UMailListWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UMailListWidget::AddMailToList(class UMailData* InMailData)
{
	if (!MailListView) return;

	UMailData* MailData = NewObject<UMailData>(this);

	MailListView->AddItem(InMailData);
	MailListView->RequestRefresh();
}

void UMailListWidget::RemoveCheckedMailToList()
{
    TArray<UUserWidget*> DisplayedWidgets = MailListView->GetDisplayedEntryWidgets();

    for (UUserWidget* Widget : DisplayedWidgets)
    {
        UMailWidget* MyMailWidget = Cast<UMailWidget>(Widget);
        if (MyMailWidget && MyMailWidget->CB_MailSelected && MyMailWidget->CB_MailSelected->IsChecked())
        {
            // 체크된 항목을 ListView에서 제거
            MailListView->RemoveItem(MyMailWidget->GetListItem());
            MailListView->RequestRefresh();
        }
    }
}
