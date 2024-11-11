
#pragma once
#include "CoreMinimal.h"
#include "GameEnums.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
    ITEM_Consumable UMETA(DisplayName = "Consumable"),
    ITEM_NoneConsumable UMETA(DisplayName = "NoneConsumable"),
    ITEM_Gold UMETA(DisplayName = "Gold"),
    ITEM_None UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class EConsumableType : uint8
{
    CONSUMABLE_HealthPotion UMETA(DisplayName = "Health"),
    CONSUMABLE_ManaPotion UMETA(DisplayName = "Mana"),
    CONSUMABLE_ExpPotion UMETA(DisplayName = "Exp"),
    CONSUMABLE_None UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class ENoneConsumableType : uint8
{
    NONECONSUMABLE_Weapon UMETA(DisplayName = "Weapon"),
    NONECONSUMABLE_Accessory UMETA(DisplayName = "Accessory"),
    NONECONSUMABLE_None      UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    WEAPON_Sword UMETA(DisplayName = "Sword"),
    WEAPON_Bow UMETA(DisplayName = "Bow"),
    WEAPON_Gun    UMETA(DisplayName = "Gun"),
    WEAPON_None      UMETA(DisplayName = "None")
};