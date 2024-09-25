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
		// 드래그가 감지되면 드래그 감지 함수로 전달
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UReceivePostalWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{    
	// UDragDropOperation 생성
	UDragDropOperation* DragDropOp = NewObject<UDragDropOperation>();
	OutOperation = DragDropOp;

	// 이동할 위젯 정보 설정
	DragDropOp->DefaultDragVisual = this; // 이 위젯을 드래그 비주얼로 사용
	DragDropOp->Pivot = EDragPivot::MouseDown; // 마우스 위치 기준으로 드래그
}

bool UReceivePostalWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	// 드래그가 끝났을 때 수행할 작업
	if (InOperation && InOperation->DefaultDragVisual == this)
	{
		// 드래그된 위치를 스크린 좌표에서 로컬 좌표로 변환
		FVector2D LocalPosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());

		// 위젯을 해당 로컬 좌표로 이동
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