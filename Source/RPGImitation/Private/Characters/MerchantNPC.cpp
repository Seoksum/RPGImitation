// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MerchantNPC.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "../RPGImitationCharacter.h"

// Sets default values
AMerchantNPC::AMerchantNPC()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = SphereComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(300.0f); // 상호작용 거리
	SphereComponent->SetupAttachment(RootComponent);
	//RootComponent = SphereComponent;

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMerchantNPC::OnPlayerEnterConversationRange);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AMerchantNPC::OnPlayerExitConversationRange);


	ConversationWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ConversationWidgetComponent"));
	ConversationWidgetComponent->SetupAttachment(RootComponent);
	ConversationWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);  
	ConversationWidgetComponent->SetDrawSize(FVector2D(100, 50));       
	ConversationWidgetComponent->SetVisibility(false);
	static ConstructorHelpers::FClassFinder<UUserWidget> PressEWidgetRef(TEXT("WidgetBlueprint'/Game/Contents/UI/Shop/WBP_PressEWidget.WBP_PressEWidget_C'"));
	if (PressEWidgetRef.Succeeded())
	{
		ConversationWidgetComponent->SetWidgetClass(PressEWidgetRef.Class);
		ConversationWidgetComponent->SetRelativeLocation(FVector(0, 0, 300));
	}
}

// Called when the game starts or when spawned
void AMerchantNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMerchantNPC::OnPlayerEnterConversationRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 플레이어가 E를 눌러 상점UI 오픈
	ARPGImitationCharacter* PlayerCharacter = Cast<ARPGImitationCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		ConversationWidgetComponent->SetVisibility(true);
		PlayerCharacter->SetPlayerCanOpenShopUI(true);
	}
}

void AMerchantNPC::OnPlayerExitConversationRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ARPGImitationCharacter* PlayerCharacter = Cast<ARPGImitationCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		ConversationWidgetComponent->SetVisibility(false);
		PlayerCharacter->SetPlayerCanOpenShopUI(false);
		PlayerCharacter->HideShopUI();
	}
}



