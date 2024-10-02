// Fill out your copyright notice in the Description page of Project Settings.


#include "UDPClient.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "HAL/RunnableThread.h"
#include "UDPReceiveRunnable.h"
#include "Characters/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUDPClient::AUDPClient()
{
    PrimaryActorTick.bCanEverTick = false;

    ServerIP = TEXT("0.0.0.0");  // 0.0.0.0���� �����Ͽ� ��� IP���� ���� ����
    ServerPort = 8001;
}

// Called when the game starts or when spawned
void AUDPClient::BeginPlay()
{
    Super::BeginPlay();

    AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    if (PlayerController)
    {
        UIManager = PlayerController->GetUIManager();
    }

    CreateSocket();
    StartClientThread();
}

void AUDPClient::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    StopConnection();
    Super::EndPlay(EndPlayReason);
}

void AUDPClient::CreateSocket()
{
    // ���� ���� �ʱ�ȭ
    FIPv4Address IPAddress;
    FIPv4Address::Parse(ServerIP, IPAddress);
    FIPv4Endpoint Endpoint(IPAddress, ServerPort);

    Socket = FUdpSocketBuilder(TEXT("UDPClientSocket"))
        .AsNonBlocking()
        .AsReusable()
        .WithBroadcast()
        .BoundToEndpoint(Endpoint)
        .WithReceiveBufferSize(2 * 1024 * 1024)
        .Build();

    if (Socket)
    {
        LocalAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
        bool bIsValid;
        LocalAddr->SetIp(*ServerIP, bIsValid);
        LocalAddr->SetPort(ServerPort);
    }

    UE_LOG(LogTemp, Log, TEXT("Create Socket ! "));
}

void AUDPClient::StartClientThread()
{
    // UDPServerRunnable ���� �� ������ ����
    ServerRunnable = MakeShared<FUDPReceiveRunnable>(Socket, LocalAddr, GetWorld(),UIManager);
    ServerThread = FRunnableThread::Create(ServerRunnable.Get(), TEXT("UDPClientRunnableThread"), 0, TPri_BelowNormal);
}

void AUDPClient::StopConnection()
{
    //bServerRunning = false;
    if (ServerThread)
    {
        ServerRunnable->Stop();
        ServerThread->Kill(true);
        delete ServerThread;
        ServerThread = nullptr;
    }

    if (Socket)
    {
        Socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
        Socket = nullptr;
    }
}
