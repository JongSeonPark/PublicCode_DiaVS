#include "AbilitySystem/Abilities/Passive/VSFireWandAbility.h"

#include "AbilitySystem/DiaAbilitySystemLibrary.h"
#include "Actor/Projectile/DiaProjectile.h"

void UVSFireWandAbility::RepeatAction(int ActionNumber)
{
	const float Rad = FMath::FRandRange(0, 2 * UE_PI);
	
	const FTransform SpawnTransform(
		FVector(FMath::Cos(Rad), FMath::Sin(Rad), 0).Rotation(),
		GetAvatarActorFromActorInfo()->GetActorLocation(),
		FVector::One() * GetArea()
		);

	AActor* SpawnActor = UDiaAbilitySystemLibrary::SpawnActorFromAbility(this, SpawnActorClass, GameplayEffectClass, SpawnTransform, false);
	const FWeaponLevelStatsRow* WeaponStatsRow = GetCurrentLevelWeaponStatsRow();
	if (ADiaProjectile* Projectile = Cast<ADiaProjectile>(SpawnActor))
	{
		Projectile->SetPierce(WeaponStatsRow->Pierce);
		Projectile->SetSpeed(GetSpeed());
	}

	SpawnActor->FinishSpawning(SpawnTransform);
}
