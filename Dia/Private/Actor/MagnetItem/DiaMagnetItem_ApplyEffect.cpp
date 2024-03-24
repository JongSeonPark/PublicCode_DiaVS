


#include "Actor/MagnetItem/DiaMagnetItem_ApplyEffect.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/DiaAbilitySystemComponent.h"
#include "AbilitySystem/DiaAbilitySystemLibrary.h"

void ADiaMagnetItem_ApplyEffect::AcceptedActorUpdate(AActor* CollisionActor)
{
	if (UDiaAbilitySystemComponent* AbilitySystemComponent = UDiaAbilitySystemLibrary::GetAbilitySystemComponent(CollisionActor))
	{
		AbilitySystemComponent->AddEffectLevel_Server( GameplayEffectClass, EffectLevel);
	}
}
