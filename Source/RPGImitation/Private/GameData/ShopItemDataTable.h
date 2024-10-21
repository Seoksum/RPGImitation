#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameData/GameEnums.h"
#include "ShopItemDataTable.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FShopItemDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	FShopItemDataTable() : ItemName("None"), ItemPath("None"), ItemType(EItemType::ITEM_None), ConsumableType(EConsumableType::CONSUMABLE_None),
		NoneConsumableType(ENoneConsumableType::NONECONSUMABLE_None), Price(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ItemPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EConsumableType ConsumableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	ENoneConsumableType NoneConsumableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Price;


};
