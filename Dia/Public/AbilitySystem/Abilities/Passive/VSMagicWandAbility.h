

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Passive/DiaVSAbility.h"
#include "VSMagicWandAbility.generated.h"

/**
 * 근접한 적의 위치에 발사체를 발사합니다.
 */
UCLASS()
class DIA_API UVSMagicWandAbility : public UDiaVSAbility
{
	GENERATED_BODY()
protected:
	virtual void RepeatAction(int ActionNumber) override;
};
