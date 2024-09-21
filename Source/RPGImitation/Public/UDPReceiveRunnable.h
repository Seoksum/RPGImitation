// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "Sockets.h"
#include "Networking.h"

/**
 * 
 */

class RPGIMITATION_API FUDPReceiveRunnable : public FRunnable
{
    // FUDPServerRunnable -> 스레드 클래스. 
     // 데이터 송수신과 같은 네트워크 작업을 비동기적으로 처리(SendData, ReceiveData)

public:

    FUDPReceiveRunnable(FSocket* InSocket, TSharedPtr<FInternetAddr> InLocalAddr, UWorld* InWorld, class UUIManager* InUIManager);
    virtual ~FUDPReceiveRunnable();

    virtual bool Init() override;
    virtual uint32 Run() override;
    virtual void Stop() override;

private:
    FSocket* Socket;
    TSharedPtr<FInternetAddr> LocalAddr;
    FRunnableThread* Thread;
    FThreadSafeBool bStopping;

    void ReceiveData();

    void SaveToJson(const FString& ReceivedMessage, UWorld* MyWorld);

    TWeakObjectPtr<UWorld> World;

    FString ReceivedString;


public:

    FIPv4Address IPAddress;  // 클라이언트 IP 주소

    int32 Port;              // 클라이언트 포트

    UPROPERTY(VisibleAnywhere)
    class UUIManager* UIManager;

};