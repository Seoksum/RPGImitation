// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/DeathInterface.h"
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

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



public:

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Attack();
	void AttackQ();
	void AttackE();
	void AttackR();

	UFUNCTION()
	void AttackHitCheck(float InDamage, float InTraceDistance, class UParticleSystem* InParticle);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	virtual void OnDeath_Implementation() override;


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
	int32 MaxAttackIndex;

	UPROPERTY(EditAnywhere, Category = "Attack")
	int32 AttackIndex = 0;

	UPROPERTY(VisibleAnywhere, Category = "State")
	bool IsDeath;


public:

	class UUIManager* GetUIManager();

	class UInventoryComponent* GetInventoryComponent();

	class UCurrencySystem* GetCurrencySystem();

	void UseInventoryItem(class UItemData* InItemData);

	// ¹«±â
	void EquipWeaponItem(const FString& WeaponName);
	USkeletalMesh* LoadWeaponMesh(FString WeaponName);

	// ¾Ç¼¼»ç¸® Âø¿ë 
	void EquipAccessory(FString ItemName, FString InSocketName);
	UStaticMesh* LoadAccMesh(FString AccName);



	// °ñµå
	void AddGold(int32 Amount);
	bool RemoveGold(int32 Amount);

	// Shop
	void SetPlayerCanOpenShopUI(bool InCanOpenShopUI);

	void ShowShopUI();
	void HideShopUI();

	void EndAttackQ();
	void EndAttackE();
	void EndAttackR();


protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Weapon")
	class AWeaponActor* CurrentWeapon;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class AWeaponActor> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class AAccessoryActor* CurrentHeadAcc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class AAccessoryActor* CurrentBagAcc;



};

