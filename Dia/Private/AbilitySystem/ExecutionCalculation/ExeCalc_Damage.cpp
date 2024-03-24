#include "AbilitySystem/ExecutionCalculation/ExeCalc_Damage.h"

#include "DiaAttributeCaptureDefs.h"
#include "DiaGameplayTags.h"
#include "AbilitySystem/DiaAttributeSet.h"

UExeCalc_Damage::UExeCalc_Damage()
{
}

void UExeCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec Spec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	float IncomingDamage = 0.f;

	IncomingDamage += Spec.GetSetByCallerMagnitude(DiaGameplayTags::Damage_Melee, false);
	IncomingDamage += Spec.GetSetByCallerMagnitude(DiaGameplayTags::Damage_Fire, false);
	IncomingDamage += Spec.GetSetByCallerMagnitude(DiaGameplayTags::Damage_Lightning, false);
	IncomingDamage += Spec.GetSetByCallerMagnitude(DiaGameplayTags::Damage_Arcane, false);

	bool bFound;
	float SourceMight = SourceASC->GetGameplayAttributeValue(UDiaAttributeSet::GetPrimaryMightAttribute(), bFound);
	float TargetArmor = TargetASC->GetGameplayAttributeValue(UDiaAttributeSet::GetPrimaryArmorAttribute(), bFound);
	if (bFound)
	{
		IncomingDamage *= 1 + SourceMight;
		IncomingDamage -= TargetArmor;
	}

	// 0 이하는 체크하지 않음
	if (IncomingDamage > 0)
	{
		const FGameplayModifierEvaluatedData EvaluatedData(UDiaAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, IncomingDamage);
		OutExecutionOutput.AddOutputModifier(EvaluatedData);
	}
}
