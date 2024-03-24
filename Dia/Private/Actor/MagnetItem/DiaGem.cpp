#include "Actor/MagnetItem/DiaGem.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DiaGameplayTags.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystem/DiaAbilitySystemLibrary.h"
#include "Character/DiaPlayerCharacter.h"
#include "Dia/Dia.h"
#include "Interaction/PlayerInterface.h"
#include "Net/UnrealNetwork.h"


ADiaGem::ADiaGem()
{
}

void ADiaGem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADiaGem, ExpBonus);
}

void ADiaGem::OnRep_ExpBonus_Implementation()
{
}

void ADiaGem::AcceptedActorUpdate(AActor* CollisionActor)
{
	if (const ADiaPlayerCharacter* PlayerCharacter = Cast<ADiaPlayerCharacter>(CollisionActor))
	{
		UAbilitySystemComponent* AbilitySystemComponent = PlayerCharacter->GetAbilitySystemComponent();
		if (!AbilitySystemComponent) return;
		
		const FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(ExpGameplayEffect, 0, ContextHandle);

		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
			SpecHandle,
			DiaGameplayTags::Attribute_Meta_InComingExp,
			ExpBonus);
		
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
	else
	{
		UE_LOG(LogDia, Warning, TEXT("%hs ADiaPlayerCharacter가 아님."), __FUNCTION__);
	}
}
