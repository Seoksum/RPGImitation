// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Components/BoxComponent.h"
#include "Components/Image.h"
#include "../RPGImitationCharacter.h"
#include "DrawDebugHelpers.h"

// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = CollisionComp;
	CollisionComp->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	CollisionComp->SetCollisionProfileName(TEXT("Trigger"));
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);

	//CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	

}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CollisionComp)
	{
		// BoxComponent의 변환 정보를 얻음
		FVector BoxLocation = CollisionComp->GetComponentLocation();
		FRotator BoxRotation = CollisionComp->GetComponentRotation();
		FVector BoxExtent = CollisionComp->GetScaledBoxExtent();

		// 디버그 박스 그리기
		DrawDebugBox(
			GetWorld(),
			BoxLocation,                 // BoxComponent의 위치
			BoxExtent,                   // BoxComponent의 크기
			BoxRotation.Quaternion(),    // BoxComponent의 회전
			FColor::Green,               // 디버그 라인 색상
			false,                       // 지속적으로 그릴 것인지 여부
			-1.0f,                       // 지속 시간 (-1이면 영구적으로 유지)
			0,                           // 우선순위
			5.0f                         // 라인 두께
		);
	}

	if (Player && CollisionComp)
	{
		// 타겟 액터와 오버랩 상태를 체크
		bool bCurrentlyOverlapping = CollisionComp->IsOverlappingActor(Player);
		if (bCurrentlyOverlapping)
		{
			//Player->SB_OnItemAcquired(this);
			Player->OnItemAcquired(this);
		}
		
	}
}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player = Cast<ARPGImitationCharacter>(OtherActor);


	//if (Player)
	//{
	//	//Player->OnItemAcquired(this);
	//	Player->SB_OnItemAcquired(this);
	//}
}

