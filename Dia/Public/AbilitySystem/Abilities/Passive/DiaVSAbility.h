#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Passive/DiaPassiveGameplayAbility.h"
#include "DiaVSAbility.generated.h"

/**
 * VS(Vampire Survivors) 방식의 자동 발사 스킬을 구현합니다.
 */
UCLASS()
class DIA_API UDiaVSAbility : public UDiaPassiveGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void AssignDefaultSetByCallerMagnitude(const FGameplayEffectSpecHandle& SpecHandle) override;
	
protected:
	virtual void OnLoopAbility();
	UFUNCTION()
	virtual void RepeatAction(int ActionNumber);

	// 시작 시 자신에게 적용, 끝날 시 삭제
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> GameplayEffectToSelfClass;
	FActiveGameplayEffectHandle GameplayEffectToSelfHandle;

	// 발사체등에 적용할 Effect
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> GameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ADiaSkillObject> SpawnActorClass;

#pragma region Stats
	UFUNCTION(BlueprintCallable, Category = "Ability")
	float GetSpeedBonus() const;
	UFUNCTION(BlueprintCallable, Category = "Ability")
	float GetSpeed() const;
	UFUNCTION(BlueprintCallable, Category = "Ability")
	float GetDurationBonus() const;
	UFUNCTION(BlueprintCallable, Category = "Ability")
	float GetAreaBonus() const;
	// 늘어나는 것에는 제한하지 않지만, 줄어드는 것에서 90%까지만 제한하겠음 
	UFUNCTION(BlueprintCallable, Category = "Ability")
	float GetCooldownBonus() const;
	UFUNCTION(BlueprintCallable, Category = "Ability")
	float GetAmountBonus() const;
	UFUNCTION(BlueprintCallable, Category = "Ability")
	int32 GetAmount() const;
	UFUNCTION(BlueprintCallable, Category = "Ability")
	float GetCooldown() const;
	UFUNCTION(BlueprintCallable, Category = "Ability")
	float GetArea() const;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	UWeaponStats* WeaponStats;
	const FWeaponLevelStatsRow* GetCurrentLevelWeaponStatsRow() const;
#pragma endregion Stats

	AActor* GetNearestEnemy() const;
	
private:
	FTimerHandle TimerHandle;

};
