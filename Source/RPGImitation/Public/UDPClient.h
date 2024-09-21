// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Networking.h"
#include "UDPReceiveRunnable.h"
#include "UDPClient.generated.h"

UCLASS()
class RPGIMITATION_API AUDPClient : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AUDPClient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


private:

	void CreateSocket();
	void StartClientThread();
	void StopConnection();

protected:

	FSocket* Socket;
	TSharedPtr<FInternetAddr> LocalAddr;
	TSharedPtr<FUDPReceiveRunnable> ServerRunnable;
	FRunnableThread* ServerThread;

	FString ServerIP;
	int32 ServerPort;

	UPROPERTY(VisibleAnywhere)
		class UUIManager* UIManager;


};
