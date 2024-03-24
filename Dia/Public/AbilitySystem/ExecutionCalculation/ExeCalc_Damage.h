

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExeCalc_Damage.generated.h"

/**
 * 데미지를 계산합니다. 프로젝트 내 모든 Damage 계산은 이 클래스로 구현되어 있습니다.
 */
UCLASS()
class DIA_API UExeCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UExeCalc_Damage();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
