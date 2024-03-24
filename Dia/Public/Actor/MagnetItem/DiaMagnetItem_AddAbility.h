

#pragma once

#include "CoreMinimal.h"
#include "Actor/MagnetItem/DiaMagnetItem.h"
#include "DiaMagnetItem_AddAbility.generated.h"

class UGameplayAbility;

/**
 * 뱀파이어 서바이버즈의 무기를 얻게 해주는 자석 아이템입니다. 
 */
UCLASS()
class DIA_API ADiaMagnetItem_AddAbility : public ADiaMagnetItem
{
	GENERATED_BODY()
protected:
	virtual void AcceptedActorUpdate(AActor* CollisionActor) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem")
	TSubclassOf<UGameplayAbility> GameplayAbilityClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem")
	int32 AddLevel = 1;
};
