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
    // FUDPServerRunnable -> ������ Ŭ����. 
     // ������ �ۼ��Ű� ���� ��Ʈ��ũ �۾��� �񵿱������� ó��(SendData, ReceiveData)

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

    FIPv4Address IPAddress;  // Ŭ���̾�Ʈ IP �ּ�

    int32 Port;              // Ŭ���̾�Ʈ ��Ʈ

    UPROPERTY(VisibleAnywhere)
    class UUIManager* UIManager;

};