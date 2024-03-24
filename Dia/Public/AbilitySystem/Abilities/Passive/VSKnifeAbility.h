#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Passive/DiaVSAbility.h"
#include "VSKnifeAbility.generated.h"

/**
 * 바라보는 방향을 향해 발사체를 발사합니다.
 */
UCLASS()
class DIA_API UVSKnifeAbility : public UDiaVSAbility
{
	GENERATED_BODY()
protected:
	virtual void RepeatAction(int ActionNumber) override;
};
