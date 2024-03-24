


#include "AbilitySystem/Abilities/Passive/VSPeachoneAbility.h"

#include "AbilitySystem/DiaAbilitySystemLibrary.h"
#include "Actor/Projectile/DiaExplosionProjectile.h"
#include "Actor/Projectile/DiaProjectileBase.h"
#include "Actor/SummonedCreature/DiaSummonedBird.h"

void UVSPeachoneAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	AActor* AvatarActor = GetAvatarActorFromActorInfo();

	FTransform SpawnTransform; 
	SummonedBird = GetWorld()->SpawnActorDeferred<ADiaSummonedBird>(
		SummonedBirdClass,
		SpawnTransform,
		AvatarActor,
		Cast<APawn>(AvatarActor));

	SummonedBird->SetInstigatorAbility(this);
	SummonedBird->FinishSpawning(SpawnTransform);
}

void UVSPeachoneAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	SummonedBird->Destroy();
}

void UVSPeachoneAbility::RepeatAction(int ActionNumber)
{
	Super::RepeatAction(ActionNumber);
	const float Rad = FMath::FRandRange(0, 2 * UE_PI);
	
	// 소환수의 위치에서 발사
	const FTransform SpawnTransform(
		FVector(FMath::Cos(Rad), FMath::Sin(Rad), 0).Rotation(),
		SummonedBird->GetFireLocation(),
		FVector::One() * GetArea()
		);

	AActor* SpawnActor = UDiaAbilitySystemLibrary::SpawnActorFromAbility(this, SpawnActorClass, GameplayEffectClass, SpawnTransform, false);
	const FWeaponLevelStatsRow* WeaponStatsRow = GetCurrentLevelWeaponStatsRow();
	if (ADiaExplosionProjectile* Projectile = Cast<ADiaExplosionProjectile>(SpawnActor))
	{
		Projectile->SetArea(GetArea());
		Projectile->SetSpeed(GetSpeed());
	}
	
	SpawnActor->FinishSpawning(SpawnTransform);
}
