#include "Actor/MagnetItem/DiaMagnetItem_AddAbility.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/DiaAbilitySystemComponent.h"
#include "AbilitySystem/DiaAbilitySystemLibrary.h"

void ADiaMagnetItem_AddAbility::AcceptedActorUpdate(AActor* CollisionActor)
{
	if (UDiaAbilitySystemComponent* AbilitySystemComponent = UDiaAbilitySystemLibrary::GetAbilitySystemComponent(CollisionActor))
	{
		AbilitySystemComponent->AddAbilityLevel_Server(GameplayAbilityClass, AddLevel);
	}
}
