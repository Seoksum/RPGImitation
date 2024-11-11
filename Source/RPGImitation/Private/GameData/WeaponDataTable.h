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

	// 무기 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WeaponName;

	// 무기 SkeletalMesh 경로
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MeshPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType WeaponType;


};