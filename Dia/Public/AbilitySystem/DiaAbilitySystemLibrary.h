#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/DiaGameplayAbility.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DiaAbilitySystemLibrary.generated.h"

class UDiaAbilitySystemComponent;
class ADiaSkillObject;
struct FScalableFloat;
struct FGameplayEffectSpecHandle;

/**
 * DiaAbilitySystem 관련 라이브러리
 */
UCLASS()
class DIA_API UDiaAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = AbilitySystem)
	static void AssignSetByCallerMagnitudes(const FGameplayEffectSpecHandle& SpecHandle, const TMap<FGameplayTag, FScalableFloat> DefaultSetByCallerTypes, float Level = 1.f);

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "AbilitySystem.Math")
	static TArray<FTransform> GetCircleAroundTransforms(const int Count, const float Radius = 1.f);

	/**
	 * 
	 * @param bIsFinishSpawning Deferred용 파라미터. false시 FinishSpawn 호출해야 함.
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem.Spawn")
	static AActor* SpawnActorFromAbility(UDiaGameplayAbility* Ability, TSubclassOf<ADiaSkillObject> SpawnActorClass, TSubclassOf<UGameplayEffect> GameplayEffectClass, const FTransform& SpawnTransform, bool bIsFinishSpawning = true);
	
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem.Ability")
	static void AddVSItemLevel_Server(UDiaAbilitySystemComponent* AbilitySystemComponent, FGameplayTag VSGameplayTag, int32 AddLevel = 1);

	UFUNCTION(BlueprintPure, Category = Ability, Meta=(DefaultToSelf = "Actor"))
	static UDiaAbilitySystemComponent* GetAbilitySystemComponent(AActor *Actor);
};
