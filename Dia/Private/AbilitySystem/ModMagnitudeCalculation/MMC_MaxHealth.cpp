#include "AbilitySystem/ModMagnitudeCalculation/MMC_MaxHealth.h"

#include "DiaAttributeCaptureDefs.h"
#include "AbilitySystem/DiaAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"

// struct FMMCMaxHealthStatics
// {
// 	FProperty* VigorProperty;
// 	FGameplayEffectAttributeCaptureDefinition VigorDef;;
//
// 	FMMCMaxHealthStatics()
// 	{
// 		VigorProperty = FindFieldChecked<FProperty>(UDiaAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UDiaAttributeSet, Vigor));
// 		VigorDef = FGameplayEffectAttributeCaptureDefinition(VigorProperty, EGameplayEffectAttributeCaptureSource::Target, false);
// 	}
// };
//
// static FMMCMaxHealthStatics& MMCMaxHealthStatics()
// {
// 	static FMMCMaxHealthStatics Statics;
// 	return Statics;
// }

UMMC_MaxHealth::UMMC_MaxHealth()
{
	// VigorDef.AttributeToCapture = UDiaAttributeSet::GetVigorAttribute();
	// VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	// VigorDef.bSnapshot = false;
	// VigorDef = FGameplayEffectAttributeCaptureDefinition(UDiaAttributeSet::GetVigorAttribute(), EGameplayEffectAttributeCaptureSource::Target, false);

	// RelevantAttributesToCapture.Add(VigorDef);
	// RelevantAttributesToCapture.Add(MMCMaxHealthStatics().VigorDef);
	// RelevantAttributesToCapture.Add(MMCMaxHealthStatics().VigorDef);
	// RelevantAttributesToCapture.Add(FDiaAttributeCaptureDefs::Get().VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters AggregatorEvaluateParameters;
	AggregatorEvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	AggregatorEvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();


	// TODO: Vigor, Level에 따른 증감값 적용 예정
	float Vigor = 1.f;
	// GetCapturedAttributeMagnitude(MMCMaxHealthStatics().VigorDef, Spec, AggregatorEvaluateParameters, Vigor);
	// GetCapturedAttributeMagnitude(FDiaAttributeCaptureDefs::Get().VigorDef, Spec, AggregatorEvaluateParameters, Vigor);
	// UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Vigor: %f"), Vigor));

	return Vigor * 10.f;
}
