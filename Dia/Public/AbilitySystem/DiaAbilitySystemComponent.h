
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DiaAbilitySystemComponent.generated.h"

/**
 * 프로젝트 내 모든 전투 캐릭터가 사용하는 AbilitySystemComponent입니다.
 * 뱀파이어 서바이버즈의 무기, 패시브 아이템들을 적용합니다.
 */
UCLASS()
class DIA_API UDiaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

#pragma region UAbilitySystemComponent interface
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnRemoveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	void OnActiveGameplayEffectAddedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
	void OnAnyGameplayEffectRemoved(const FActiveGameplayEffect& ActiveGameplayEffect);
#pragma endregion
	
	UFUNCTION(BlueprintCallable, Reliable, Server, Category = "AbilitySystem.Ability")
	void AddAbilityLevel_Server(TSubclassOf<UGameplayAbility> GameplayAbilityClass, int32 AddLevel = 1);
	UFUNCTION(BlueprintCallable, Reliable, Server, Category = "AbilitySystem.Effect")
	void AddEffectLevel_Server(TSubclassOf<UGameplayEffect> GameplayEffectClass, int32 AddLevel = 1);
	
	UFUNCTION(BlueprintCallable, Reliable, Server, Category = "AbilitySystem.Ability")
	void RemoveVSAbility_Server(FGameplayTag VSTag);
	UFUNCTION(BlueprintCallable, Reliable, Server, Category = "AbilitySystem.Effect")
	void RemoveVSEffect_Server(FGameplayTag VSTag);
	
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> GetVSGameplayAbilitySpecHandles() const { return VSGameplayAbilitySpecHandles; }
	TMap<FGameplayTag, FActiveGameplayEffectHandle> GetVSGameplayEffectHandles() const { return VSGameplayEffectHandles; }
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "VS")
	int32 GetVSItemLevel(FGameplayTag VSTag) const;
	
private:
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> VSGameplayAbilitySpecHandles;
	TMap<FGameplayTag, FActiveGameplayEffectHandle> VSGameplayEffectHandles;
	
};
