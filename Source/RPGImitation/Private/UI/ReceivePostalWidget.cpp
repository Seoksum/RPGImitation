// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ReceivePostalWidget.h"
#include "Items/MailData.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UReceivePostalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

FReply UReceivePostalWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		// �巡�װ� �����Ǹ� �巡�� ���� �Լ��� ����
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UReceivePostalWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{    
	// UDragDropOperation ����
	UDragDropOperation* DragDropOp = NewObject<UDragDropOperation>();
	OutOperation = DragDropOp;

	// �̵��� ���� ���� ����
	DragDropOp->DefaultDragVisual = this; // �� ������ �巡�� ���־�� ���
	DragDropOp->Pivot = EDragPivot::MouseDown; // ���콺 ��ġ �������� �巡��
}

bool UReceivePostalWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	// �巡�װ� ������ �� ������ �۾�
	if (InOperation && InOperation->DefaultDragVisual == this)
	{
		// �巡�׵� ��ġ�� ��ũ�� ��ǥ���� ���� ��ǥ�� ��ȯ
		FVector2D LocalPosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());

		// ������ �ش� ���� ��ǥ�� �̵�
		SetRenderTranslation(LocalPosition);

		return true;
	}

	return false;
}

void UReceivePostalWidget::SetMail(class UMailData* Mail)
{
	T_Sender->SetText(FText::FromString(Mail->Sender));
	T_Title->SetText(FText::FromString(Mail->Title));
	T_Message->SetText(FText::FromString(Mail->Message));
}