// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MailData.generated.h"

/**
 * 
 */
UCLASS()
class RPGIMITATION_API UMailData : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MailData")
		FString Sender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MailData")
		FString Message;
};
