#include "AbilitySystem/DiaAbilitySystemGlobals.h"

#include "DiaGameplayTags.h"
#include "AbilitySystem/DiaGameplayEffectContext.h"

FGameplayEffectContext* UDiaAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FDiaGameplayEffectContext();
}

void UDiaAbilitySystemGlobals::InitGlobalTags()
{
	ActivateFailIsDeadTag = DiaGameplayTags::Activation_Fail_IsDead;
	ActivateFailCooldownTag = DiaGameplayTags::Activation_Fail_OnCooldown;
	ActivateFailCostTag = DiaGameplayTags::Activation_Fail_CantAffordCost;
	ActivateFailTagsBlockedTag = DiaGameplayTags::Activation_Fail_BlockedByTags;
	ActivateFailTagsMissingTag = DiaGameplayTags::Activation_Fail_MissingTags;
	ActivateFailNetworkingTag = DiaGameplayTags::Activation_Fail_Networking;
}
