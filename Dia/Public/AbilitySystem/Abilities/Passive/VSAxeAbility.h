

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Passive/DiaVSAbility.h"
#include "VSAxeAbility.generated.h"

/**
 * XY방향으로 중력이 작동하는 Axe를 발사합니다.
 * XY 축에서 30~120도 방향으로 랜덤하게 발사합니다.
 */
UCLASS()
class DIA_API UVSAxeAbility : public UDiaVSAbility
{
	GENERATED_BODY()
protected:
	virtual void RepeatAction(int ActionNumber) override;
};
