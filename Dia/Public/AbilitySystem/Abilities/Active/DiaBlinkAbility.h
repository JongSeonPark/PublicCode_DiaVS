

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DiaGameplayAbility.h"
#include "DiaBlinkAbility.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class DIA_API UDiaBlinkAbility : public UDiaGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UFUNCTION(BlueprintCallable, Category = "Blink")
	void BlinkToLocation(const FVector& GoalLocation);
};
