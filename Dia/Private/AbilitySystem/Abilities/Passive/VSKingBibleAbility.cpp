


#include "AbilitySystem/Abilities/Passive/VSKingBibleAbility.h"

#include "AbilitySystemComponent.h"
#include "Actor/DiaWhirl.h"

void UVSKingBibleAbility::OnLoopAbility()
{
	AActor* Avatar = GetAvatarActorFromActorInfo();
	const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	const FWeaponLevelStatsRow* SkillDataRow = GetCurrentLevelWeaponStatsRow();
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Avatar->GetActorLocation());
	SpawnTransform.SetScale3D(FVector::One() * SkillDataRow->Area);

	ADiaWhirl* Whirl = GetWorld()->SpawnActorDeferred<ADiaWhirl>(SpawnActorClass, SpawnTransform, Avatar, Cast<APawn>(Avatar));
	Whirl->SetActorLocation(Avatar->GetActorLocation());
	Whirl->SetLifeSpan(SkillDataRow->Duration);

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(Whirl);

	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, GetAbilityLevel(), EffectContextHandle);
	AssignDefaultSetByCallerMagnitude(EffectSpecHandle);
	Whirl->SetEffectSpecHandle(EffectSpecHandle);

	Whirl->FinishSpawning(SpawnTransform);
}
