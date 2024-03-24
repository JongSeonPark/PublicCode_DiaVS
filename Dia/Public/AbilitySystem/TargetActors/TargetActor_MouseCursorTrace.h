

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Trace.h"
#include "TargetActor_MouseCursorTrace.generated.h"

/**
 * Deprecated. 프로젝트 내 사용되지 않음.
 */
UCLASS()
class DIA_API ATargetActor_MouseCursorTrace : public AGameplayAbilityTargetActor_Trace
{
	GENERATED_BODY()
public:
	ATargetActor_MouseCursorTrace();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> RootSceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDecalComponent> DecalComponent;
	
protected:
	virtual FHitResult PerformTrace(AActor* InSourceActor) override;
};
