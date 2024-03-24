

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Passive/DiaVSAbility.h"
#include "VSPeachoneAbility.generated.h"

class ADiaSummonedBird;
/**
 * 소환수를 소환하고, 소환수의 위치에 따라 발사체를 발사합니다.
 */
UCLASS()
class DIA_API UVSPeachoneAbility : public UDiaVSAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void RepeatAction(int ActionNumber) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADiaSummonedBird> SummonedBirdClass;
	TObjectPtr<ADiaSummonedBird> SummonedBird;
	
};
