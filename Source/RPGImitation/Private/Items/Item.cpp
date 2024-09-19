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

	ItemName = FText::FromString("HpPotion");
	const FString ThumbnailPath = "Texture2D'/Game/Contents/Images/potion.potion'";
	Thumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ThumbnailPath));
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
		// BoxComponent�� ��ȯ ������ ����
		FVector BoxLocation = CollisionComp->GetComponentLocation();
		FRotator BoxRotation = CollisionComp->GetComponentRotation();
		FVector BoxExtent = CollisionComp->GetScaledBoxExtent();

		// ����� �ڽ� �׸���
		DrawDebugBox(
			GetWorld(),
			BoxLocation,                 // BoxComponent�� ��ġ
			BoxExtent,                   // BoxComponent�� ũ��
			BoxRotation.Quaternion(),    // BoxComponent�� ȸ��
			FColor::Green,               // ����� ���� ����
			false,                       // ���������� �׸� ������ ����
			-1.0f,                       // ���� �ð� (-1�̸� ���������� ����)
			0,                           // �켱����
			5.0f                         // ���� �β�
		);
	}
}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARPGImitationCharacter* Player = Cast<ARPGImitationCharacter>(OtherActor);
	if (Player)
	{
		Player->OnItemAcquired(this);
	}

}

FText AItem::GetItemName()
{
	return ItemName;
}



