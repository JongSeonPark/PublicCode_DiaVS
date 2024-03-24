#include "AbilitySystem/Abilities/DiaGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/DiaAbilitySystemLibrary.h"
#include "AbilitySystem/DiaGameplayEffectContext.h"

UDiaGameplayAbility::UDiaGameplayAbility()
{
	// 이 옵션은 종종 문제를 일으킵니다.
	// 즉, 클라이언트의 GameplayAbility가 취소 또는 자연 완료로 인해 종료되면 서버의 버전이 완료되었는지 여부에 관계없이 강제로 종료됩니다.
	// 후자의 문제는 특히 지연 시간이 긴 플레이어가 사용하는 로컬 예측 GameplayAbility의 경우 중요한 문제입니다.
	// 일반적으로 이 옵션을 비활성화하는 것이 좋습니다.
	bServerRespectsRemoteAbilityCancellation = false;
}

FGameplayEffectContextHandle UDiaGameplayAbility::MakeEffectContext(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const
{
	FGameplayEffectContextHandle EffectContextHandle = Super::MakeEffectContext(Handle, ActorInfo);
	const FGameplayEffectContext* EffectContext = FDiaGameplayEffectContext::ExtractEffectContext(EffectContextHandle);
	check(EffectContext);
	check(ActorInfo);

	return EffectContextHandle;
}

void UDiaGameplayAbility::AssignDefaultSetByCallerMagnitude(const FGameplayEffectSpecHandle& SpecHandle)
{
	UDiaAbilitySystemLibrary::AssignSetByCallerMagnitudes(SpecHandle, DefaultSetByCallerTypes, GetAbilityLevel());
}
