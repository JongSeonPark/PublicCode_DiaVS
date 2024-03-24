


#include "AbilitySystem/Abilities/Passive/VSDeathSpiralAbility.h"

#include "AbilitySystem/DiaAbilitySystemLibrary.h"
#include "Actor/Projectile/DiaProjectile.h"


void UVSDeathSpiralAbility::OnLoopAbility()
{
	TArray<FTransform> Transforms = UDiaAbilitySystemLibrary::GetCircleAroundTransforms(GetCurrentLevelWeaponStatsRow()->Amount);
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	for (FTransform Transform : Transforms)
	{
		Transform.SetLocation(Location);
		AActor* SpawnActor = UDiaAbilitySystemLibrary::SpawnActorFromAbility(this, SpawnActorClass, GameplayEffectClass, Transform, false);
		const FWeaponLevelStatsRow* WeaponLevelStatsRow = GetCurrentLevelWeaponStatsRow();
		if (ADiaProjectile* Projectile = Cast<ADiaProjectile>(SpawnActor))
		{
			if (WeaponLevelStatsRow)
				Projectile->SetPierce(WeaponLevelStatsRow->Pierce);
			Projectile->SetSpeed(GetSpeed());
		}
		SpawnActor->FinishSpawning(Transform);
	}
}
