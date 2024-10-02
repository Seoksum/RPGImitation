// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChatSystem.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnMessageReceived, const FString&);

UCLASS()
class RPGIMITATION_API AChatSystem : public AActor
{
	GENERATED_BODY()
	
public:	

	AChatSystem();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSendMessage(const FString& Message);
	bool ServerSendMessage_Validate(const FString& Message);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastReceiveMessage(const FString& Message);


	FOnMessageReceived OnMessageReceived;

	virtual void OnRep_Owner() override;

	UPROPERTY(EditAnywhere, Category = "UI")
	class UChatWidget* ChatWidget;

	// 위젯 클래스 참조
	UPROPERTY(BlueprintReadWrite, Category = "UI", Meta = (BlueprintProtected = true))
	TSubclassOf<class UChatWidget> ChatWidgetClass;



protected:
	
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

};
