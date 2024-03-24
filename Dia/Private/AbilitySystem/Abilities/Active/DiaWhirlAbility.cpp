


#include "AbilitySystem/Abilities/Active/DiaWhirlAbility.h"

#include "AbilitySystemComponent.h"
#include "Actor/DiaWhirl.h"

void UDiaWhirlAbility::SpawnWhirl()
{
	if (!HasAuthority(&CurrentActivationInfo))
		return;
	
	AActor* Avatar = GetAvatarActorFromActorInfo();
	const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Avatar->GetActorLocation());
	SpawnTransform.SetScale3D(FVector::One() * Area);

	ADiaWhirl* Whirl = GetWorld()->SpawnActorDeferred<ADiaWhirl>(WhirlClass, SpawnTransform, Avatar, Cast<APawn>(Avatar));
	Whirl->SetActorLocation(Avatar->GetActorLocation());
	Whirl->SetLifeSpan(Duration);

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(Whirl);

	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, GetAbilityLevel(), EffectContextHandle);
	AssignDefaultSetByCallerMagnitude(EffectSpecHandle);
	Whirl->SetEffectSpecHandle(EffectSpecHandle);

	Whirl->FinishSpawning(SpawnTransform);
}
