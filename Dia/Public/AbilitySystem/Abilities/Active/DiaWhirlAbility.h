

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DiaGameplayAbility.h"
#include "DiaWhirlAbility.generated.h"

class ADiaWhirl;
/**
 * 
 */
UCLASS()
class DIA_API UDiaWhirlAbility : public UDiaGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Whirl")
	TSubclassOf<class UGameplayEffect> GameplayEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Whirl")
	TSubclassOf<ADiaWhirl> WhirlClass;
	
	UFUNCTION(BlueprintCallable, Category = "Whirl")
	void SpawnWhirl();

	// 나중에 PlayerAttribute를 참조
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Whirl")
	float TimePerSpawn = 3.f;
	
	// 나중에 PlayerAttribute를 참조
	UPROPERTY(EditDefaultsOnly, Category = "Whirl")
	float Duration = 2.f;
	
	// 나중에 PlayerAttribute를 참조
	UPROPERTY(EditDefaultsOnly, Category = "Whirl")
	float Area = 1.f;
};
