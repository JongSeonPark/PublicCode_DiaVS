#include "AbilitySystem/Abilities/Active/DiaProjectileAbility.h"

#include "AbilitySystemComponent.h"
#include "Actor/Projectile/DiaProjectile.h"
#include "Kismet/KismetSystemLibrary.h"

void UDiaProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UDiaProjectileAbility::SpawnProjectile(const FVector& TargetLocation, const FGameplayTag& SocketTag)
{
	if (!HasAuthority(&CurrentActivationInfo))
		return;

	const AActor* AvatarActor = GetAvatarActorFromActorInfo();
	FTransform SpawnTransform;

	// TODO: Socket으로 정함
	SpawnTransform.SetLocation(AvatarActor->GetActorLocation());

	FRotator Rotation = (TargetLocation - AvatarActor->GetActorLocation()).Rotation();
	Rotation.Pitch = 0;
	SpawnTransform.SetRotation(Rotation.Quaternion());
	
	SpawnProjectile_Transform(SpawnTransform);
}

void UDiaProjectileAbility::SpawnProjectile_Transform(const FTransform& SpawnTransform)
{
	if (!HasAuthority(&CurrentActivationInfo))
		return;

	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	const UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();

	ADiaProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADiaProjectile>(
		ProjectileClass,
		SpawnTransform,
		AvatarActor,
		Cast<APawn>(AvatarActor));

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(Projectile);

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, GetAbilityLevel(), EffectContextHandle);
	AssignDefaultSetByCallerMagnitude(SpecHandle);
	Projectile->SetEffectSpecHandle(SpecHandle);

	Projectile->FinishSpawning(SpawnTransform);
}
