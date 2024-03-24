#include "AbilitySystem/Abilities/Passive/VSMagicWandAbility.h"

#include "AbilitySystem/DiaAbilitySystemLibrary.h"
#include "Actor/Projectile/DiaProjectile.h"
#include "Actor/Projectile/DiaProjectileBase.h"
#include "Character/DiaCharacterBase.h"
#include "GameFramework/ProjectileMovementComponent.h"

void UVSMagicWandAbility::RepeatAction(int ActionNumber)
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	AActor* NearestEnemy = GetNearestEnemy();
	FTransform SpawnTransform;
	if (NearestEnemy)
	{
		SpawnTransform = FTransform(
			(NearestEnemy->GetActorLocation() - AvatarActor->GetActorLocation()).Rotation(),
			AvatarActor->GetActorLocation(),
			FVector::One() * GetArea()
		);
	}
	else
	{
		// 없으면 랜덤 방향으로 발사
		const float Rad = FMath::FRandRange(0, 2 * UE_PI);

		SpawnTransform = FTransform(
			FVector(FMath::Cos(Rad), FMath::Sin(Rad), 0).Rotation(),
			GetAvatarActorFromActorInfo()->GetActorLocation(),
			FVector::One() * GetArea()
		);
	}

	AActor* SpawnActor = UDiaAbilitySystemLibrary::SpawnActorFromAbility(this, SpawnActorClass, GameplayEffectClass, SpawnTransform, false);
	const FWeaponLevelStatsRow* WeaponStatsRow = GetCurrentLevelWeaponStatsRow();
	if (ADiaProjectile* Projectile = Cast<ADiaProjectile>(SpawnActor))
	{
		Projectile->SetPierce(WeaponStatsRow->Pierce);
		Projectile->SetSpeed(GetSpeed());
	}

	SpawnActor->FinishSpawning(SpawnTransform);
}
