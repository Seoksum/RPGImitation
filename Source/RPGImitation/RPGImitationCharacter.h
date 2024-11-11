// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/DeathInterface.h"
#include "GameData/GameEnums.h"
#include "RPGImitationCharacter.generated.h"

UCLASS(config=Game)
class ARPGImitationCharacter : public ACharacter, public IDeathInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ARPGImitationCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void Tick(float DeltaTime) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



public:

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Attack();
	void AttackEnd();

	void AttackQ();
	void AttackE();
	void AttackR();

	UFUNCTION()
	void AttackHitCheck(float InDamage, float InTraceDistance, class UParticleSystem* InParticle);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	virtual void OnDeath_Implementation() override;

	void IncreaseExp(int32 Exp);

	void LevelUp(int32 PlayerLevel);


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class UMyAnimInstance* AnimInstance;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UUIManager* UIManager;

	UPROPERTY(BlueprintReadWrite, Category = "Stat")
	class UStatComponent* Stat;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	class UWidgetComponent* StatBar;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	class UInventoryComponent* Inventory;

	UPROPERTY(BlueprintReadWrite, Category = "Currency")
	class UCurrencySystem* CurrencySystem;

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Shop")
	bool CanOpenShopUI;

	UPROPERTY(BlueprintReadWrite, Category = "Attack")
	float Radius;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool IsAttacking = false;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool IsAttackingQ = false;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool IsAttackingE = false;

	UPROPERTY(VisibleAnywhere, Category = "Attack")
	bool IsAttackingR = false;

	UPROPERTY(EditAnywhere, Category = "Attack")
	uint8 MaxAttackIndex;

	UPROPERTY(EditAnywhere, Category = "Attack")
	uint8 AttackIndex = 0;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool IsDeath;

	UPROPERTY(EditAnywhere, Category = "Attack")
	int32 CurrentLevel;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float RequiredMana;

	UPROPERTY(EditAnywhere, Category = "CameraZoom")
	bool bWantsToZoom;

	UPROPERTY(EditDefaultsOnly, Category = "CameraZoom")
	float ZoomedFOV;

	UPROPERTY(EditDefaultsOnly, Category = "CameraZoom")
	float DefaultFOV;

	// 보간 속도를 0.1 ~ 100 사이 값
	UPROPERTY(EditDefaultsOnly, Category = "CameraZoom", meta = (ClampMin = 0.1f, ClampMax = 100.f))
	float ZoomInterpSpeed;



public:

	class UUIManager* GetUIManager();

	class UInventoryComponent* GetInventoryComponent();

	class UCurrencySystem* GetCurrencySystem();

	class UStatComponent* GetStatComponent();

	bool GetIsPlayerDead();

	void UseInventoryItem(class UItemData* InItemData);


	// 무기
	void EquipWeaponItem(const FString& WeaponName, FString InSocketName);

	//USkeletalMesh* LoadWeaponMesh(FString WeaponName);
	TPair<USkeletalMesh*,EWeaponType> LoadWeaponMesh(FString WeaponName);

	// 악세사리 착용 
	void EquipAccessory(FString ItemName, FString InSocketName);
	UStaticMesh* LoadAccMesh(FString AccName);

	void SwitchWeapon(int32 InWeaponIndex, class UWeaponItemDataAsset* WeaponItem); // 무기 교체 UI


public:

	// 골드
	void AddGold(int32 Amount);
	bool RemoveGold(int32 Amount);

	// Shop
	void SetPlayerCanOpenShopUI(bool InCanOpenShopUI);

	void ShowShopUI();
	void HideShopUI();

	void EndAttackQ();
	void EndAttackE();
	void EndAttackR();

	EWeaponType GetCurrentWeaponType();

	FVector GetWeaponMeshSocketLocation(const FName& SocketName);

	void DrinkHpPotion(float Amount);
	void DrinkManaPotion(float Amount);
	void DrinkExpPotion(float Amount);

	void CameraZoom(const float Value);
	void BeginZoom();
	void EndZoom();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	EWeaponType CurrentWeaponType;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Weapon")
	class AWeaponActor* CurrentWeapon;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class AWeaponActor> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class AAccessoryActor* CurrentHeadAcc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class AAccessoryActor* CurrentBagAcc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		class UWeaponItemData_Sword* WeaponItem_Sword;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UWeaponItemData_Gun* WeaponItem_Gun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UWeaponItemData_Bow* WeaponItem_Bow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		class UParticleSystem* LevelupEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
		class USoundBase* LevelupSound;



};

