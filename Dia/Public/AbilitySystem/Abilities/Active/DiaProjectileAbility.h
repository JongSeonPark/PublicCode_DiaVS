

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/DiaGameplayAbility.h"
#include "DiaProjectileAbility.generated.h"

/**
 * 
 */
UCLASS()
class DIA_API UDiaProjectileAbility : public UDiaGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& TargetLocation, const FGameplayTag& SocketTag);
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile_Transform(const FTransform& SpawnTransform);

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> GameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ADiaProjectile> ProjectileClass;

};
