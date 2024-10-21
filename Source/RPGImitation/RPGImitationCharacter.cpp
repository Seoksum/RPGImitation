// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGImitationCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/StatComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFrameworks/MyGameModeBase.h"
#include "Managers/UIManager.h"
#include "Managers/CurrencySystem.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/MyPlayerController.h"
#include "Items/ItemData.h"
#include "Items/WeaponItemData.h"
#include "Items/WeaponActor.h"
#include "Items/AccessoryActor.h"
#include "Engine/DataTable.h"
#include "GameData/WeaponDataTable.h"
#include "UI/Stat/StatBarWidget.h"
#include "Characters/MyAnimInstance.h"

ARPGImitationCharacter::ARPGImitationCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Stat = CreateDefaultSubobject<UStatComponent>(TEXT("Stat"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	CurrencySystem = CreateDefaultSubobject<UCurrencySystem>(TEXT("Currency"));

	StatBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	StatBar->SetupAttachment(GetMesh());
	StatBar->SetRelativeLocation(FVector(0.f, 0.f, 220.f));
	StatBar->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/Contents/UI/Stat/WBP_PlayerStatBar.WBP_PlayerStatBar_C'"));
	if (UW.Succeeded())
	{
		StatBar->SetWidgetClass(UW.Class);
		StatBar->SetDrawSize(FVector2D(200.f, 50.f));
	}

	Radius = 200.f;
	MaxAttackIndex = 3;
	IsAttacking = false;
	IsAttackingQ = false;
}

void ARPGImitationCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARPGImitationCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARPGImitationCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ARPGImitationCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ARPGImitationCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Shop", IE_Pressed, this, &ARPGImitationCharacter::ShowShopUI);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ARPGImitationCharacter::Attack);
	PlayerInputComponent->BindAction(TEXT("AttackQ"), EInputEvent::IE_Pressed, this, &ARPGImitationCharacter::AttackQ);
	PlayerInputComponent->BindAction(TEXT("AttackE"), EInputEvent::IE_Pressed, this, &ARPGImitationCharacter::AttackE);
	PlayerInputComponent->BindAction(TEXT("AttackR"), EInputEvent::IE_Pressed, this, &ARPGImitationCharacter::AttackR);
}

void ARPGImitationCharacter::BeginPlay()
{
	Super::BeginPlay();

	Stat->SetLevelStat(1);

	CurrentWeapon = GetWorld()->SpawnActor<AWeaponActor>(AWeaponActor::StaticClass());
	CurrentHeadAcc = GetWorld()->SpawnActor< AAccessoryActor>(AAccessoryActor::StaticClass());
	CurrentBagAcc = GetWorld()->SpawnActor< AAccessoryActor>(AAccessoryActor::StaticClass());

	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		UIManager = PlayerController->GetUIManager();
	}

	StatBar->InitWidget();
	UStatBarWidget* StatBarWidget = Cast<UStatBarWidget>(StatBar->GetUserWidgetObject());
	if (StatBarWidget)
	{
		StatBarWidget->BindHp(Stat);
		StatBarWidget->BindMana(Stat);
	}
}

void ARPGImitationCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnAttackHit.AddUObject(this, &ARPGImitationCharacter::AttackHitCheck);
		AnimInstance->OnAttackHit_Q.AddUObject(this, &ARPGImitationCharacter::AttackHitCheck);
		AnimInstance->OnAttackHit_E.AddUObject(this, &ARPGImitationCharacter::AttackHitCheck);
		AnimInstance->OnAttackHit_R.AddUObject(this, &ARPGImitationCharacter::AttackHitCheck);

		AnimInstance->OnMontageEnded.AddDynamic(this, &ARPGImitationCharacter::OnAttackMontageEnded);
	}
}

void ARPGImitationCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ARPGImitationCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ARPGImitationCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ARPGImitationCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

UUIManager* ARPGImitationCharacter::GetUIManager()
{
	if (nullptr == UIManager) { UIManager = NewObject<UUIManager>(); }
	return UIManager;
}

UInventoryComponent* ARPGImitationCharacter::GetInventoryComponent()
{
	if (nullptr == Inventory) { Inventory = NewObject<UInventoryComponent>(); }
	return Inventory;
}

UCurrencySystem* ARPGImitationCharacter::GetCurrencySystem()
{
	if (nullptr == CurrencySystem) { CurrencySystem = NewObject<UCurrencySystem>(); }
	return CurrencySystem;
}

void ARPGImitationCharacter::UseInventoryItem(class UItemData* InItemData)
{
	// 아이템 고유 능력 발동
	Inventory->RemoveItem(InItemData);
}

void ARPGImitationCharacter::EquipWeaponItem(const FString& WeaponName)
{
	USkeletalMesh* WeaponMesh = LoadWeaponMesh(WeaponName);
	if (WeaponMesh) { CurrentWeapon->AttachWeaponToSocket(this, "RightHand_SwordSocket", WeaponMesh); }
}

USkeletalMesh* ARPGImitationCharacter::LoadWeaponMesh(FString WeaponName)
{
	static const FString ContextString(TEXT("Weapon Context"));
	UDataTable* NoneConsumableItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/Contents/Data/NoneConsumableItemDataTable.NoneConsumableItemDataTable'"));
	if (NoneConsumableItemDataTable)
	{
		FNoneConsumableItemDataTable* WeaponData = NoneConsumableItemDataTable->FindRow<FNoneConsumableItemDataTable>(*WeaponName, ContextString);
		if (WeaponData)
		{
			USkeletalMesh* WeaponMesh = LoadObject<USkeletalMesh>(nullptr, *WeaponData->MeshPath);
			return WeaponMesh;
		}
	}
	return nullptr;
}

void ARPGImitationCharacter::EquipAccessory(FString ItemName, FString InSocketName)
{
	UStaticMesh* AccMesh = LoadAccMesh(ItemName);
	if (InSocketName.Equals("HeadAccSocket")) { CurrentHeadAcc->AttachAccessoryToSocket(this, FName(*InSocketName), AccMesh); }
	else if (InSocketName.Equals("BagAccSocket")) { CurrentBagAcc->AttachAccessoryToSocket(this, FName(*InSocketName), AccMesh); }
}

UStaticMesh* ARPGImitationCharacter::LoadAccMesh(FString AccName)
{
	static const FString ContextString(TEXT("Acc Context"));
	UDataTable* NoneConsumableItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/Contents/Data/NoneConsumableItemDataTable.NoneConsumableItemDataTable'"));
	if (NoneConsumableItemDataTable)
	{
		FNoneConsumableItemDataTable* AccessoryData = NoneConsumableItemDataTable->FindRow<FNoneConsumableItemDataTable>(*AccName, ContextString);
		if (AccessoryData)
		{
			UStaticMesh* AccessoryMesh = LoadObject<UStaticMesh>(nullptr, *AccessoryData->MeshPath);
			return AccessoryMesh;
		}
	}
	return nullptr;
}

void ARPGImitationCharacter::AddGold(int32 Amount)
{
	CurrencySystem->AddGold(Amount);
}

bool ARPGImitationCharacter::RemoveGold(int32 Amount)
{
	if (CurrencySystem)
	{
		return CurrencySystem->RemoveGold(Amount);
	}
	return false;
}

void ARPGImitationCharacter::ShowShopUI()
{
	if (CanOpenShopUI)
	{
		UIManager->UpdateUIState(EUIState::UI_Shop, CanOpenShopUI);
	}
}
void ARPGImitationCharacter::HideShopUI()
{
	UIManager->UpdateUIState(EUIState::UI_Shop, CanOpenShopUI);
}

void ARPGImitationCharacter::SetPlayerCanOpenShopUI(bool InCanOpenShopUI)
{
	CanOpenShopUI = InCanOpenShopUI;
}

float ARPGImitationCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Stat->OnAttacked(DamageAmount);
	return DamageAmount;
}

void ARPGImitationCharacter::OnDeath_Implementation()
{
	if (IsDeath)
		return;

	IsDeath = true;

	AMyGameModeBase* MyGameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	if (MyGameMode)
	{
		MyGameMode->PawnKilled(this);
	}

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	DisableInput(PlayerController);
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARPGImitationCharacter::Attack()
{
	if (IsAttacking)
		return;

	IsAttacking = true;
	AnimInstance->PlayAttackMontage();
	AnimInstance->JumpToSection(AttackIndex);
	AttackIndex = (AttackIndex + 1) % MaxAttackIndex;
}

void ARPGImitationCharacter::AttackQ()
{
	if (IsAttackingQ)
		return;

	IsAttackingQ = true;
	AnimInstance->PlayAttackMontageQ();
	UIManager->StartSkillAttackQ();
}

void ARPGImitationCharacter::AttackE()
{
	if (IsAttackingE)
		return;

	IsAttackingE = true;
	AnimInstance->PlayAttackMontageE();
	UIManager->StartSkillAttackE();
}

void ARPGImitationCharacter::AttackR()
{
	if (IsAttackingR)
		return;

	IsAttackingR = true;
	AnimInstance->PlayAttackMontageR();
	UIManager->StartSkillAttackR();
}

void ARPGImitationCharacter::AttackHitCheck(float InDamage, float InTraceDistance, class UParticleSystem* InParticle)
{
	TArray<FHitResult> TraceHits;
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = TraceStart + (GetActorForwardVector() * InTraceDistance);
	FCollisionShape SweepShape = FCollisionShape::MakeSphere(Radius);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bResult = GetWorld()->SweepMultiByChannel(TraceHits, TraceStart, TraceEnd,
		FQuat::Identity, ECC_GameTraceChannel1, SweepShape, QueryParams);
	if (bResult)
	{
		for (FHitResult& Hit : TraceHits)
		{
			FDamageEvent DamageEvent;
			Hit.Actor->TakeDamage(InDamage, DamageEvent, GetController(), this);
			if (InParticle)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), InParticle, Hit.Actor->GetTransform());
			}
		}
	}
}

void ARPGImitationCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}
void ARPGImitationCharacter::EndAttackQ()
{
	IsAttackingQ = false;
}
void ARPGImitationCharacter::EndAttackE()
{
	IsAttackingE = false;
}
void ARPGImitationCharacter::EndAttackR()
{
	IsAttackingR = false;
}

