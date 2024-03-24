#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/DiaVSItemDatas.h"
#include "DiaGameplayAbility.generated.h"

/**
 * 게임 내 사용되는 GameplayAbility들의 부모 클래스입니다.
 */
UCLASS()
class DIA_API UDiaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UDiaGameplayAbility();

	virtual FGameplayEffectContextHandle MakeEffectContext(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const override;
	virtual void AssignDefaultSetByCallerMagnitude(const FGameplayEffectSpecHandle& SpecHandle);
	
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (Categories="InputTag"))
	FGameplayTag StartupInputTag;
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FScalableFloat> DefaultSetByCallerTypes;
};
