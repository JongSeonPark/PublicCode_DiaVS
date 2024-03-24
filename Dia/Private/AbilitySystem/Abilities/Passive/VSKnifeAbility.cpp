#include "AbilitySystem/Abilities/Passive/VSKnifeAbility.h"

#include "Abilities/Tasks/AbilityTask_Repeat.h"
#include "AbilitySystem/DiaAbilitySystemLibrary.h"
#include "Actor/Projectile/DiaProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

void UVSKnifeAbility::RepeatAction(int ActionNumber)
{
	// 위치 값 보정
	// 나이프의 위치를 바라보는 값 기준으로 X(0~100), Y(-50~50)만큼 이동
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const float Rad = FMath::Atan2(Forward.X, Forward.Y);
	FVector CorrectionLocation = FVector(FMath::FRandRange(0.f, 100.f), FMath::FRandRange(-50.f, 50.f), 0);
	CorrectionLocation = CorrectionLocation.RotateAngleAxisRad(Rad, FVector::ZAxisVector);
	const FTransform SpawnTransform(
		GetAvatarActorFromActorInfo()->GetActorRotation(),
		GetAvatarActorFromActorInfo()->GetActorLocation() + CorrectionLocation,
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
