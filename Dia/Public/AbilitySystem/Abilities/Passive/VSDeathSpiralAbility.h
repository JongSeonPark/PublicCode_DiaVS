

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Passive/DiaVSAbility.h"
#include "VSDeathSpiralAbility.generated.h"

/**
 * 사방을 향해 발사체를 발사합니다.
 * 발사체의 수에 따라 360도를 n등분하여 발사합니다.
 */
UCLASS()
class DIA_API UVSDeathSpiralAbility : public UDiaVSAbility
{
	GENERATED_BODY()
public:
	virtual void OnLoopAbility() override;
};
