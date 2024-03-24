
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SendGameplayEvent.generated.h"

/**
 * Animation 중간에 GameplayEvent를 발생시킬 때 사용됩니다.
 */
UCLASS(const, hidecategories=Object, collapsecategories, Config = Game, meta=(DisplayName="Send Gameplay Event"), MinimalAPI)
class UAnimNotify_SendGameplayEvent : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_SendGameplayEvent();
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
protected:
	UPROPERTY(EditAnywhere, meta=(Categories="Event"))
	FGameplayTag EventTag;
};
