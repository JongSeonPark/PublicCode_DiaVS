

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DiaInputConfig.generated.h"

class UInputAction;

/**
 * Active Ability를 위한 InputTag를 지정하기 위한 struct입니다.
 */
USTRUCT(BlueprintType)
struct FDiaInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, meta=(Categories="InputTag"))
	FGameplayTag InputTag = FGameplayTag();
};


UCLASS()
class DIA_API UDiaInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FDiaInputAction> InputActions;
};
