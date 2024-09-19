// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/TriggerItemPickup.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Items/Item.h"
#include "../RPGImitationCharacter.h"

// Sets default values
ATriggerItemPickup::ATriggerItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;
	CollisionComp->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	CollisionComp->SetCollisionProfileName(TEXT("Trigger"));
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATriggerItemPickup::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ATriggerItemPickup::BeginPlay()
{
	Super::BeginPlay();

}

void ATriggerItemPickup::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ItemClass)
	{
		FVector SpawnLocation = GetActorLocation();  // 스폰할 위치 설정
		FRotator SpawnRotation = GetActorRotation();  // 스폰할 회전 값 설정
		FActorSpawnParameters SpawnParams;
		Item = GetWorld()->SpawnActor<AItem>(ItemClass, SpawnLocation, SpawnRotation, SpawnParams);
	}
}

void ATriggerItemPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARPGImitationCharacter* Player = Cast<ARPGImitationCharacter>(OtherActor);
	if (Player)
	{
		Player->OnItemAcquired(Item);
		//UE_LOG(LogTemp, Log, TEXT("Character Trigger On ! "));
	}

}



