

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Passive/DiaVSAbility.h"
#include "VSLightningRingAbility.generated.h"

/**
 * LightningRing을 구현하는 Ability 클래스입니다.
 */
UCLASS()
class DIA_API UVSLightningRingAbility : public UDiaVSAbility
{
	GENERATED_BODY()
protected:
	virtual void OnLoopAbility() override;
	virtual void RepeatAction(int ActionNumber) override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ANiagaraActor> SpawnNiagaraActorClass;
private:
	TArray<AActor*> LightningTargets;
};
