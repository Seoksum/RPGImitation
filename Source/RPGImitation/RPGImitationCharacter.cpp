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
#include "Items/WeaponItemData_Gun.h"
#include "Items/WeaponItemData_Bow.h"
#include "Items/WeaponItemData_Sword.h"
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
	CurrentWeaponType = EWeaponType::WEAPON_None;
	CurrentLevel = 1;

	ZoomedFOV = 65.f;
	ZoomInterpSpeed = 20.f;
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
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ARPGImitationCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ARPGImitationCharacter::LookUpAtRate);

	//PlayerInputComponent->BindAction(TEXT("Zoom"), EInputEvent::IE_Pressed, this, &ARPGImitationCharacter::BeginZoom);
	//PlayerInputComponent->BindAction(TEXT("Zoom"), EInputEvent::IE_Released, this, &ARPGImitationCharacter::EndZoom);
	PlayerInputComponent->BindAxis(TEXT("CameraZoom"), this, &ARPGImitationCharacter::CameraZoom);

	PlayerInputComponent->BindAction("Shop", IE_Pressed, this, &ARPGImitationCharacter::ShowShopUI);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ARPGImitationCharacter::Attack);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Released, this, &ARPGImitationCharacter::AttackEnd);

	PlayerInputComponent->BindAction(TEXT("AttackQ"), EInputEvent::IE_Pressed, this, &ARPGImitationCharacter::AttackQ);
	PlayerInputComponent->BindAction(TEXT("AttackE"), EInputEvent::IE_Pressed, this, &ARPGImitationCharacter::AttackE);
	PlayerInputComponent->BindAction(TEXT("AttackR"), EInputEvent::IE_Pressed, this, &ARPGImitationCharacter::AttackR);


}

void ARPGImitationCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeapon = GetWorld()->SpawnActor<AWeaponActor>(AWeaponActor::StaticClass());
	CurrentWeapon->SetOwner(this);
	CurrentHeadAcc = GetWorld()->SpawnActor< AAccessoryActor>(AAccessoryActor::StaticClass());
	CurrentBagAcc = GetWorld()->SpawnActor< AAccessoryActor>(AAccessoryActor::StaticClass());

	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PlayerController)
	{
		UIManager = PlayerController->GetUIManager();
	}

	if (Stat)
	{
		Stat->SetLevelStat(CurrentLevel);
		RequiredMana = Stat->GetTotalStat().Mana;
		Stat->OnAddWeaponAttack.AddUObject(UIManager, &UUIManager::UpdateWeaponAttackStat);
		Stat->OnStatChanged.AddUObject(UIManager, &UUIManager::UpdatePlayerStat);
		Stat->OnPlayerLevelUp.AddUObject(this, &ARPGImitationCharacter::LevelUp);
		Stat->OnPlayerLevelUp.AddUObject(UIManager, &UUIManager::UpdatePlayerLevel);
		UIManager->BindWidget(Stat);
	}

	StatBar->InitWidget();
	UStatBarWidget* StatBarWidget = Cast<UStatBarWidget>(StatBar->GetUserWidgetObject());
	if (StatBarWidget)
	{
		StatBarWidget->BindHp(Stat);
		StatBarWidget->BindMana(Stat);
	}

	DefaultFOV = FollowCamera->FieldOfView;
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

void ARPGImitationCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 줌인 & 줌아웃
	if (CurrentWeaponType == EWeaponType::WEAPON_Gun || CurrentWeaponType == EWeaponType::WEAPON_Bow)
	{
		float TargetFOV = bWantsToZoom ? ZoomedFOV : DefaultFOV;
		float NewFOV = FMath::FInterpTo(FollowCamera->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);
		FollowCamera->SetFieldOfView(NewFOV);
	}
}

void ARPGImitationCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ARPGImitationCharacter::LookUpAtRate(float Rate)
{
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

void ARPGImitationCharacter::CameraZoom(const float Value)
{
	if (Value == 0.f)
		return;

	const float NewTargetArmLength = CameraBoom->TargetArmLength + Value * 10.f;
	CameraBoom->TargetArmLength = FMath::Clamp(NewTargetArmLength, 200.f, 1000.f);
}

void ARPGImitationCharacter::BeginZoom()
{
	bWantsToZoom = true;
}

void ARPGImitationCharacter::EndZoom()
{
	bWantsToZoom = false;
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

UStatComponent* ARPGImitationCharacter::GetStatComponent()
{
	if (nullptr == Stat) { Stat = NewObject<UStatComponent>(); }
	return Stat;
}

bool ARPGImitationCharacter::GetIsPlayerDead()
{
	return IsDeath;
}

void ARPGImitationCharacter::UseInventoryItem(class UItemData* InItemData)
{
	// 아이템 고유 능력 발동
	Inventory->RemoveItem(InItemData);
}

EWeaponType ARPGImitationCharacter::GetCurrentWeaponType() { return CurrentWeaponType; }

FVector ARPGImitationCharacter::GetWeaponMeshSocketLocation(const FName& SocketName)
{
	return CurrentWeapon->GetMuzzleSocketLocation(SocketName);
}

void ARPGImitationCharacter::DrinkHpPotion(float Amount)
{
	if (Stat) { Stat->UseHpPotion(Amount); }
}

void ARPGImitationCharacter::DrinkManaPotion(float Amount)
{
	if (Stat) { Stat->UseManaPotion(Amount); }
}

void ARPGImitationCharacter::DrinkExpPotion(float Amount)
{
	if (Stat) { Stat->SetExp(Amount); }
}


void ARPGImitationCharacter::EquipWeaponItem(const FString& WeaponName, FString InSocketName)
{
	TPair<USkeletalMesh*, EWeaponType> WeaponPair = LoadWeaponMesh(WeaponName);
	if (WeaponPair.Key != nullptr)
	{
		CurrentWeapon->AttachWeaponToSocket(this, FName(*InSocketName), WeaponPair.Key);
	}

	CurrentWeaponType = WeaponPair.Value;
	if (CurrentWeaponType == EWeaponType::WEAPON_Sword)
	{
		if (nullptr == WeaponItem_Sword)
		{
			WeaponItem_Sword = NewObject<UWeaponItemData_Sword>(GetWorld());
			WeaponItem_Sword->InitializeWorld(GetWorld());
			WeaponItem_Sword->SetOwner(this);
		}
		Stat->SetWeaponStat(WeaponItem_Sword->GetWeaponStat());
	}
	else if (CurrentWeaponType == EWeaponType::WEAPON_Gun)
	{
		if (nullptr == WeaponItem_Gun)
		{
			WeaponItem_Gun = NewObject<UWeaponItemData_Gun>(GetWorld());
			WeaponItem_Gun->InitializeWorld(GetWorld());
			WeaponItem_Gun->SetOwner(this);
		}
		Stat->SetWeaponStat(WeaponItem_Gun->GetWeaponStat());
	}
	else if (CurrentWeaponType == EWeaponType::WEAPON_Bow)
	{
		if (nullptr == WeaponItem_Bow)
		{
			WeaponItem_Bow = NewObject<UWeaponItemData_Bow>(GetWorld());
			WeaponItem_Bow->InitializeWorld(GetWorld());
			WeaponItem_Bow->SetOwner(this);
		}
		Stat->SetWeaponStat(WeaponItem_Bow->GetWeaponStat());
	}
}

TPair<USkeletalMesh*, EWeaponType> ARPGImitationCharacter::LoadWeaponMesh(FString WeaponName)
{
	TPair<USkeletalMesh*, EWeaponType> Ret;
	static const FString ContextString(TEXT("Weapon Context"));
	UDataTable* NoneConsumableItemDataTable = LoadObject<UDataTable>
		(nullptr, TEXT("DataTable'/Game/Contents/Data/NoneConsumableItemDataTable.NoneConsumableItemDataTable'"));

	if (NoneConsumableItemDataTable)
	{
		FNoneConsumableItemDataTable* WeaponData = NoneConsumableItemDataTable->FindRow<FNoneConsumableItemDataTable>(*WeaponName, ContextString);
		if (WeaponData)
		{
			USkeletalMesh* WeaponMesh = LoadObject<USkeletalMesh>(nullptr, *WeaponData->MeshPath);
			EWeaponType WeaponType = WeaponData->WeaponType;
			Ret.Key = WeaponMesh;
			Ret.Value = WeaponType;
			return Ret;
		}
	}
	return Ret;
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
	UDataTable* NoneConsumableItemDataTable = LoadObject<UDataTable>
		(nullptr, TEXT("DataTable'/Game/Contents/Data/NoneConsumableItemDataTable.NoneConsumableItemDataTable'"));

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

void ARPGImitationCharacter::SwitchWeapon(int32 InWeaponIndex, UWeaponItemDataAsset* WeaponItem)
{
	
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

//float ARPGImitationCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
//{
//	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
//	Stat->OnAttacked(DamageAmount);
//	return DamageAmount;
//}

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

void ARPGImitationCharacter::IncreaseExp(int32 Exp)
{
	Stat->SetExp(Exp);
}

void ARPGImitationCharacter::LevelUp(int32 PlayerLevel)
{	
	// 파티클,사운드 생성
	UGameplayStatics::SpawnEmitterAttached(LevelupEffect, GetMesh());
	UGameplayStatics::PlaySoundAtLocation(this, LevelupSound, GetActorLocation());

	// 레벨업
	CurrentLevel = PlayerLevel;
	Stat->SetLevelStat(CurrentLevel); // 체력,마나 MAX 값으로 설정
}

void ARPGImitationCharacter::Attack()
{
	if (IsAttacking) return;

	if (CurrentWeaponType == EWeaponType::WEAPON_Sword)
	{
		IsAttacking = true;
		AnimInstance->PlayAttackMontage();
		AnimInstance->JumpToSection(AttackIndex);
		AttackIndex = (AttackIndex + 1) % MaxAttackIndex;
	}
	else if (CurrentWeaponType == EWeaponType::WEAPON_Gun && WeaponItem_Gun)
	{
		WeaponItem_Gun->StartFire();
	}
	else if (CurrentWeaponType == EWeaponType::WEAPON_Bow && WeaponItem_Bow)
	{
		AnimInstance->PlayBowAttackMontage();
		WeaponItem_Bow->Attack();
	}
}

void ARPGImitationCharacter::AttackEnd()
{
	if (CurrentWeaponType == EWeaponType::WEAPON_Gun && WeaponItem_Gun)
	{
		WeaponItem_Gun->StopFire();
		IsAttacking = false;
	}
}

void ARPGImitationCharacter::AttackQ()
{
	if (CurrentWeaponType != EWeaponType::WEAPON_Sword
		|| IsAttackingQ || Stat->GetCurrentMana() < RequiredMana)
		return;

	IsAttackingQ = true;
	Stat->OnAttacking(RequiredMana);
	AnimInstance->PlayAttackMontageQ();
	UIManager->StartSkillAttackQ();
}

void ARPGImitationCharacter::AttackE()
{
	if (CurrentWeaponType != EWeaponType::WEAPON_Sword || IsAttackingE || Stat->GetCurrentMana() < RequiredMana+5.f)
		return;

	IsAttackingE = true;
	Stat->OnAttacking(RequiredMana+5.f);
	AnimInstance->PlayAttackMontageE();
	UIManager->StartSkillAttackE();
}

void ARPGImitationCharacter::AttackR()
{
	if (CurrentWeaponType != EWeaponType::WEAPON_Sword || IsAttackingR || Stat->GetCurrentMana() < RequiredMana + 10.f)
		return;

	IsAttackingR = true;
	Stat->OnAttacking(RequiredMana + 10.f);
	AnimInstance->PlayAttackMontageR();
	UIManager->StartSkillAttackR();
}

void ARPGImitationCharacter::AttackHitCheck(float InDamage, float InTraceDistance, class UParticleSystem* InParticle)
{
	if (WeaponItem_Sword) { WeaponItem_Sword->Attack(InDamage, InTraceDistance, InParticle); }
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

