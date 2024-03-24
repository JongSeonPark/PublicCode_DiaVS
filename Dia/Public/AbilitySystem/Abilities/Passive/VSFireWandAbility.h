

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Passive/DiaVSAbility.h"
#include "VSFireWandAbility.generated.h"

/**
 * 랜덤한 방향으로 발사체를 발사합니다.
 */
UCLASS()
class DIA_API UVSFireWandAbility : public UDiaVSAbility
{
	GENERATED_BODY()
protected:
	virtual void RepeatAction(int ActionNumber) override;
};
