// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterSelection.generated.h"

UCLASS()
class RPGIMITATION_API ACharacterSelection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterSelection();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	void NextOrBefore(bool IsNext);

	UPROPERTY(VisibleAnywhere)
	int32 CharacterMeshIdx = 0;

	USkeletalMesh* GetSelectedSkeletalMesh();

	//Scene Component
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* CharacterSceneComp;

	UPROPERTY(VisibleAnywhere)
	TArray<USkeletalMeshComponent*> CharacterMeshArray;

	USkeletalMeshComponent* NowSkeletalMesh;
};
