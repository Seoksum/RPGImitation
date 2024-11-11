// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterSelectionWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/CharacterSelection.h"
#include "GameFrameworks/MyGameInstance.h"

void UCharacterSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SelectorActor = Cast<ACharacterSelection>(UGameplayStatics::GetActorOfClass(this, CurrentCharSelect));

}

void UCharacterSelectionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_SelectCharacter->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::PressSelectBtn);

	NextBtn->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::PressNextBtn);
	BeforeBtn->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::PressBeforeBtn);

}

void UCharacterSelectionWidget::PressSelectBtn()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}

	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->SetCharacterMeshIndex(SelectorActor->GetSelectedSkeletalMesh());
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMap"), true);
}

void UCharacterSelectionWidget::PressNextBtn()
{
	SelectorActor->NextOrBefore(true);
}

void UCharacterSelectionWidget::PressBeforeBtn()
{
	SelectorActor->NextOrBefore(false);
}

