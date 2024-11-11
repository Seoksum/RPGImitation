#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameData/GameEnums.h"
#include "WeaponDataTable.generated.h"


USTRUCT(BlueprintType)
struct FNoneConsumableItemDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	// ���� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WeaponName;

	// ���� SkeletalMesh ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MeshPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType WeaponType;


};