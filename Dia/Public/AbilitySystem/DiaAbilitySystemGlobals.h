

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "DiaAbilitySystemGlobals.generated.h"

/**
 * FDiaGameplayEffectContext로 통신하기 위해 사용했습니다.
 * Config(DefaultGame.ini)내에서 UAbilitySystemGlobals를 교체합니다.
 */
UCLASS(Config=Game)
class DIA_API UDiaAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
public:
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	// 코드상에 GameplayTag가 있으므로 굳이 config를 통해서 지정하는 방식을 사용하지 않겠음.
	// 추가로 사용할 글로벌 테그가 있다면 사용하겠음.
	virtual void InitGlobalTags() override;
	
};
