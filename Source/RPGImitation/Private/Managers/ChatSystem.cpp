// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/ChatSystem.h"
#include "Net/UnrealNetwork.h"

AChatSystem::AChatSystem()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	bAlwaysRelevant = true;
	bReplicates = true;

}

void AChatSystem::BeginPlay()
{
	Super::BeginPlay();
	
	OnRep_Owner();
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
	HandleChatMessage(Message);
	//OnMessageReceived.Broadcast(Message);
	UE_LOG(LogTemp, Warning, TEXT("Message received: %s"), *Message);
}

void AChatSystem::HandleChatMessage(const FString& Message)
{
	// 델리게이트를 통해 UI에 메시지 전달
	OnMessageReceived.Broadcast(Message);
}

void AChatSystem::OnRep_Owner()
{
	Super::OnRep_Owner();

	// 클라이언트에서 소유권이 올바르게 설정되었는지 확인
	if (GetOwner() != nullptr)
		UE_LOG(LogTemp, Warning, TEXT("ChatSystem owner on client: %s"), *GetOwner()->GetName());
	if (GetOwner() == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("No Owner"));
}

void AChatSystem::SetOwningOwner(AActor* NewOwner)
{
	if (HasAuthority() && NewOwner)  // 서버에서만 소유자 설정
	{
		SetOwner(NewOwner);  // SetOwner()로 소유자 설정

		if (GetOwner() == NewOwner)  // 소유자 확인
		{
			UE_LOG(LogTemp, Warning, TEXT("Owner is successfully set to: %s"), *NewOwner->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to set Owner."));
		}
	}
}

void AChatSystem::OnRep_MyOwner()
{
	//MyOwner = Cast<class AMyPlayerController>(GetOwner());
	if (MyOwner)
	{
		SetOwningOwner(MyOwner);
	}
	else
	{
		SetOwningOwner(nullptr);
	}
}


void AChatSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


}