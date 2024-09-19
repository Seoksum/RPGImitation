// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

USTRUCT(BlueprintType)
struct RPGIMITATION_API FItemData
{
	GENERATED_BODY()

public:
	// 아이템 이름
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	FText ItemName;

	// 아이템 이미지
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item")
	UTexture2D* ItemImage;

};

UCLASS()
class RPGIMITATION_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* CollisionComp;


protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

public:


	FText GetItemName();


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FItemData ItemData;


public:


	UPROPERTY(EditAnywhere, Category = "Item")
	class UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, Category = "Item")
	FText ItemName;

	UPROPERTY(EditAnywhere, Category = "Item")  // meta = (MultiLine = true))
	FText ItemDescription;




};
