
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StatDataTable.generated.h"

USTRUCT(BlueprintType)
struct FStatDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float AttackQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float AttackE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float AttackR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
		float Mana;

	FStatDataTable operator+(const FStatDataTable& other) const
	{
		FStatDataTable Result;

		const float* BaseStat = reinterpret_cast<const float*>(this);
		const float* OtherStat = reinterpret_cast<const float*>(&other);
		float* ResultStat = reinterpret_cast<float*>(&Result);

		int32 StatNum = sizeof(FStatDataTable) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultStat[i] = BaseStat[i] + OtherStat[i];
		}
		return Result;
	}
};

