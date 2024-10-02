// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/ChatSystem.h"
#include "Net/UnrealNetwork.h"
#include "UI/ChatWidget.h"
#include "Characters/MyPlayerController.h"
#include "Managers/UIManager.h"

AChatSystem::AChatSystem()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	bReplicates = true;
	bAlwaysRelevant = true;
	bNetUseOwnerRelevancy = true;
}

void AChatSystem::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("ChatSystem running on server"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ChatSystem running on client (replicated)"));
	}

	//OnRep_Owner();
}

void AChatSystem::ServerSendMessage_Implementation(const FString& Message)
{
	MulticastReceiveMessage(Message);
}

bool AChatSystem::ServerSendMessage_Validate(const FString& Message)
{
	return true;
}

void AChatSystem::MulticastReceiveMessage_Implementation(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("MulticastReceiveMessage called on client with message: %s"), *Message);
	OnMessageReceived.Broadcast(Message);
}

void AChatSystem::OnRep_Owner()
{
	Super::OnRep_Owner();

	// 클라이언트에서 소유권이 올바르게 설정되었는지 확인
	//if (GetOwner() != nullptr)
	//	UE_LOG(LogTemp, Warning, TEXT("ChatSystem owner on client: %s"), *GetOwner()->GetName());
	//if (GetOwner() == nullptr)
	//	UE_LOG(LogTemp, Warning, TEXT("No Owner"));
}


void AChatSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


}