
#pragma once


#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/Abilities/DiaGameplayAbility.h"
#include "DiaPassiveGameplayAbility.generated.h"

/**
 * Avatar에 등록되자마자 바로 Active되는 Ability입니다.
 */
UCLASS()
class DIA_API UDiaPassiveGameplayAbility : public UDiaGameplayAbility
{
	GENERATED_BODY()
public:
	UDiaPassiveGameplayAbility();
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	UPROPERTY(EditDefaultsOnly)
	bool bActivateAbilityOnGranted = true;

};
