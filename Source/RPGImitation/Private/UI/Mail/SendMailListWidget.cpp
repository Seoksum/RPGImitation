// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Mail/SendMailListWidget.h"
#include "Components/ListView.h"
#include "Components/CheckBox.h"
#include "UI/Mail/SendMailWidget.h"
#include "Items/MailData.h"

void USendMailListWidget::NativeConstruct()
{
    Super::NativeConstruct();

}

void USendMailListWidget::AddMailToList(class UMailData* InMailData)
{
    if (!SendMailListView) return;

    SendMailListView->AddItem(InMailData);
    SendMailListView->RequestRefresh();
}

void USendMailListWidget::RemoveCheckedMailToList()
{
    TArray<UUserWidget*> DisplayedWidgets = SendMailListView->GetDisplayedEntryWidgets();

    for (UUserWidget* Widget : DisplayedWidgets)
    {
        USendMailWidget* MyMailWidget = Cast<USendMailWidget>(Widget);
        if (MyMailWidget && MyMailWidget->CB_MailSelected && MyMailWidget->CB_MailSelected->IsChecked())
        {
            // üũ�� �׸��� ListView���� ����
            SendMailListView->RemoveItem(MyMailWidget->GetListItem());
            SendMailListView->RequestRefresh();
        }
    }
}

void USendMailListWidget::CheckAllMail(bool IsChecked)
{
    //TArray<UUserWidget*> DisplayedWidgets = SendMailListView->GetDisplayedEntryWidgets();
    //for (UUserWidget* Widget : DisplayedWidgets)
    //{
    //    USendMailWidget* MyMailWidget = Cast<USendMailWidget>(Widget);
    //    MyMailWidget->CB_MailSelected->SetIsChecked(IsChecked);
    //}

    TArray<UObject*> AllItems = SendMailListView->GetListItems();
    for (UObject* Item : AllItems)
    {
        USendMailWidget* MyMailWidget = Cast<USendMailWidget>(SendMailListView->GetEntryWidgetFromItem(Item));
        if (MyMailWidget && MyMailWidget->CB_MailSelected)
        {
            MyMailWidget->CB_MailSelected->SetIsChecked(true);  // üũ�ڽ��� üũ ���·� ����
        }
    }
}

bool USendMailListWidget::CanDeleteSentMail()
{
    TArray<UUserWidget*> DisplayedWidgets = SendMailListView->GetDisplayedEntryWidgets();

    for (UUserWidget* Widget : DisplayedWidgets)
    {
        USendMailWidget* MyMailWidget = Cast<USendMailWidget>(Widget);
        if (MyMailWidget && MyMailWidget->CB_MailSelected && MyMailWidget->CB_MailSelected->IsChecked())
        {
            return true;
        }
    }
    return false;
}