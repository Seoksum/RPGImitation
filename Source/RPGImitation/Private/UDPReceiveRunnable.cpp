// Fill out your copyright notice in the Description page of Project Settings.


#include "UDPReceiveRunnable.h"
#include "Networking.h"
#include "Kismet/GameplayStatics.h"
#include "UDPClient.h"
#include "Managers/UIManager.h"
#include "Items/MailData.h"


FUDPReceiveRunnable::FUDPReceiveRunnable(FSocket* InSocket, TSharedPtr<FInternetAddr> InLocalAddr, UWorld* InWorld, class UUIManager* InUIManager)
    : Socket(InSocket), LocalAddr(InLocalAddr), bStopping(false), World(InWorld), UIManager(InUIManager)
{
    Thread = FRunnableThread::Create(this, TEXT("UDPClientRunnableThread"), 0, TPri_BelowNormal);

}

FUDPReceiveRunnable::~FUDPReceiveRunnable()
{
    if (Thread)
    {
        Thread->Kill(true);
        delete Thread;
        Thread = nullptr;
    }
}

bool FUDPReceiveRunnable::Init()
{
    return (Socket != nullptr && LocalAddr.IsValid());
}

uint32 FUDPReceiveRunnable::Run()
{
    // 서버 스레드의 메인 루프
    while (!bStopping)
    {
        ReceiveData();
        FPlatformProcess::Sleep(0.1f);  // 서버가 과도하게 CPU를 사용하지 않도록 대기
    }

    return 0;
}

void FUDPReceiveRunnable::Stop()
{
    bStopping = true;
}

void FUDPReceiveRunnable::ReceiveData()
{
    TArray<uint8> ReceivedData;
    ReceivedData.SetNumUninitialized(1024);

    int32 BytesRead = 0;
    TSharedRef<FInternetAddr> Sender = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();


    // 데이터 수신
    if (Socket->RecvFrom(ReceivedData.GetData(), ReceivedData.Num(), BytesRead, *Sender))
    {
        if (BytesRead > 0)
        {
            ReceivedString = FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(ReceivedData.GetData())));
            UE_LOG(LogTemp, Log, TEXT("Received : %s"), *ReceivedString);
            AsyncTask(ENamedThreads::GameThread, [this]()
                {
                    // UWorld를 사용한 작업은 반드시 게임 스레드에서 실행되어야 합니다.
                    // ValidWorld에서 필요한 작업 수행
                    if (World.IsValid())
                    {
                        if (nullptr != UIManager)
                        {
                            UMailData* MailData = NewObject<UMailData>();
                            if (MailData)
                            {
                                MailData->Sender = "Server";
                                MailData->Message = ReceivedString;

                                UIManager->AddMailToMailBox(MailData);
                            }
                        }
                    }
                });

        }
    }
}

void FUDPReceiveRunnable::SaveToJson(const FString& ReceivedMessage, UWorld* MyWorld)
{
    //TArray<FString> Paths;
    //ReceivedMessage.ParseIntoArray(Paths, TEXT("."));

    //if (Paths.Num() < MinimumStringLen)
    //    return;

    //if (Paths.Num() == MinimumStringLen)
    //{
    //    UConnectionGameInstance* GameInstance = Cast<UConnectionGameInstance>(UGameplayStatics::GetGameInstance(World.Get()));
    //    if (GameInstance)
    //    {
    //        GameInstance->SaveToJson(Paths[0], Paths[1], Paths[2]);
    //    }
    //}

}



