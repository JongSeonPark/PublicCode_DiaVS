

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "Actor/MagnetItem/DiaMagnetItem.h"
#include "DiaMagnetItem_ApplyEffect.generated.h"

class UGameplayEffect;

/**
 * 뱀파이어 서바이버즈의 패시브 아이템을 얻게 해주는 자석 아이템입니다. 
 */
UCLASS()
class DIA_API ADiaMagnetItem_ApplyEffect : public ADiaMagnetItem
{
	GENERATED_BODY()
protected:
	virtual void AcceptedActorUpdate(AActor* CollisionActor) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem")
	TMap<FGameplayTag, FScalableFloat> DefaultSetByCallerTypes;
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem")
	float EffectLevel = 1.f;
};
