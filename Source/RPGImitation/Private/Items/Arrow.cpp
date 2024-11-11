// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Arrow.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AArrow::AArrow()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComp->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	MeshComp->SetCollisionProfileName(FName("CharacterMesh"));

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionComp->SetBoxExtent(FVector(60.f, 40.f, 20.f));
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComp->SetCollisionProfileName(TEXT("Arrow"));
	CollisionComp->SetSimulatePhysics(false);
	CollisionComp->SetGenerateOverlapEvents(true);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AArrow::OnBeginOverlap);
	RootComponent = CollisionComp;
	MeshComp->SetupAttachment(CollisionComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComp->UpdatedComponent = CollisionComp;
	ProjectileMovementComp->ProjectileGravityScale = 1.f;
	ProjectileMovementComp->InitialSpeed = 5000.f;
	ProjectileMovementComp->MaxSpeed = 5000.f;
	ProjectileMovementComp->bRotationFollowsVelocity = false;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;

	SetActorLocation(FVector(0.f, 0.f, 30.f));

	MuzzleSocketName = "MuzzleSocket";
	InitialLifeSpan = 3.f;
	BaseDamage = 30.f;
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();

	if (DefaultEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(DefaultEffect, MeshComp, MuzzleSocketName);
	}
}

void AArrow::OnBeginOverlap(UPrimitiveComponent* OverlappedcComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SkillEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(SkillEffect, MeshComp);
	}
	FDamageEvent DamageEvent;
	OtherActor->TakeDamage(BaseDamage, DamageEvent, OtherActor->GetInstigatorController(), this);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AArrow::SetArrowSpeed(float ArrowSpeedVal)
{
	ProjectileMovementComp->InitialSpeed = ArrowSpeedVal;
}
