


#include "AbilitySystem/AnimNotify_SendGameplayEvent.h"

#include "AbilitySystemBlueprintLibrary.h"

UAnimNotify_SendGameplayEvent::UAnimNotify_SendGameplayEvent()
{
}

void UAnimNotify_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	FGameplayEventData EventData;
	EventData.Instigator = MeshComp->GetOwner()->GetInstigator(); 
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, EventData);
	
	Super::Notify(MeshComp, Animation, EventReference);
}
