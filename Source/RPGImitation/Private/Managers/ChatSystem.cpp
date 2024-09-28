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
	// ��������Ʈ�� ���� UI�� �޽��� ����
	OnMessageReceived.Broadcast(Message);
}

void AChatSystem::OnRep_Owner()
{
	Super::OnRep_Owner();

	// Ŭ���̾�Ʈ���� �������� �ùٸ��� �����Ǿ����� Ȯ��
	if (GetOwner() != nullptr)
		UE_LOG(LogTemp, Warning, TEXT("ChatSystem owner on client: %s"), *GetOwner()->GetName());
	if (GetOwner() == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("No Owner"));
}

void AChatSystem::SetOwningOwner(AActor* NewOwner)
{
	if (HasAuthority() && NewOwner)  // ���������� ������ ����
	{
		SetOwner(NewOwner);  // SetOwner()�� ������ ����

		if (GetOwner() == NewOwner)  // ������ Ȯ��
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