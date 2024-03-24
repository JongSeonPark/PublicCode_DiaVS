#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DiaSummonedCreature.generated.h"

class UDiaGameplayAbility;

/**
 * Ability로 인하여 소환된 크리처입니다.
 * Peachone, Ebony Wings 등을 구현합니다.
 */
UCLASS()
class DIA_API ADiaSummonedCreature : public AActor
{
	GENERATED_BODY()

public:
	ADiaSummonedCreature();
	void SetInstigatorAbility(UDiaGameplayAbility* Ability) { InstigatorAbility = Ability; }

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> SkeltalMesh;
	TObjectPtr<UDiaGameplayAbility> InstigatorAbility;
};
