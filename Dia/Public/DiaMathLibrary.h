#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DiaMathLibrary.generated.h"

/**
 * 수학 및 랜덤 관련 함수를 포함하겠음.
 */
UCLASS()
class DIA_API UDiaMathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// 랜덤 가중치 알고리즘 적용
	// TPair가 UFUNCTION에 적용되지 않아서 단지 전역함수로 적용
	// 이미 정렬되어 있다면 bSort를 false로 적용
	template <typename T>
	static TArray<TPair<T, float>> WeightedRandomSelection(TArray<TPair<T, float>> Items, bool bShouldSort = true, int32 NumSelections = 1);

	// Array를 랜덤하게 섞습니다.
	template <typename T>
	static void ShuffleArray(TArray<T>& Array);
};

template <typename T>
TArray<TPair<T, float>> UDiaMathLibrary::WeightedRandomSelection(TArray<TPair<T, float>> Items, bool bShouldSort, int32 NumSelections)
{
	TArray<TPair<T, float>> Result;
	if (Items.Num() == 0) return Result;
	
	// 복사해서 본래 값이 변동 없게 적용
	TArray<TPair<T, float>> AvailableItems(Items);
	if (bShouldSort)
	{
		AvailableItems.Sort([](const TPair<T, float> A, const TPair<T, float> B)
		{
			return A.Value > B.Value;
		});
	}

	float TotalWeight = 0;
	for (TPair<T, float> Item : AvailableItems)
	{
		TotalWeight += Item.Value;
	}

	// 가중치 알고리즘 적용
	for (int32 i = 0; i < NumSelections; i++)
	{
		float RandomValue = FMath::FRand() * TotalWeight;
		for(TPair<T, float> Item : AvailableItems)
		{
			RandomValue -= Item.Value;
			if (RandomValue <= 0)
			{
				Result.Add(Item);
				AvailableItems.Remove(Item);
				TotalWeight -= Item.Value;
				break;
			}
		}
	}

	return Result;
}

template <typename T>
void UDiaMathLibrary::ShuffleArray(TArray<T>& Array)
{
	for (int32 i = 0; i < Array.Num(); i++)
	{
		float ShuffleIndex = FMath::RandRange(0, Array.Num() - 1);
		if (i != ShuffleIndex)
			Array.Swap(i, ShuffleIndex);
	}
}
