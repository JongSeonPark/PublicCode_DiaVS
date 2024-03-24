

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Passive/DiaVSAbility.h"
#include "VSKingBibleAbility.generated.h"

/**
 * 주변을 도는 WhirlObject를 소환합니다.
 */
UCLASS()
class DIA_API UVSKingBibleAbility : public UDiaVSAbility
{
	GENERATED_BODY()
protected:
	virtual void OnLoopAbility() override;
};
