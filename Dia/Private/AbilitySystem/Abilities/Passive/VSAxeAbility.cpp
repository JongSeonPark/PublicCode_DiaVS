#include "AbilitySystem/Abilities/Passive/VSAxeAbility.h"

#include "Abilities/Tasks/AbilityTask_Repeat.h"
#include "AbilitySystem/DiaAbilitySystemLibrary.h"
#include "Actor/Projectile/DiaAxe.h"

void UVSAxeAbility::RepeatAction(int ActionNumber)
{
	const FTransform SpawnTransform(
		FQuat::Identity,
		GetAvatarActorFromActorInfo()->GetActorLocation(),
		FVector::One() * GetArea()
	);
	
	AActor* SpawnActor = UDiaAbilitySystemLibrary::SpawnActorFromAbility(this, SpawnActorClass, GameplayEffectClass, SpawnTransform, false);
	const FWeaponLevelStatsRow* WeaponStatsRow = GetCurrentLevelWeaponStatsRow();
	if (ADiaAxe* Axe = Cast<ADiaAxe>(SpawnActor))
	{
		static const float VelocityMultiplyValue = 1000.f;

		// 랜덤하게 60~120도 방향으로 Velocity를 초기값으로 줌
		const float Rad = FMath::FRandRange(UE_PI / 3, UE_PI * 2 / 3);
		const FVector AxeVelocity(FMath::Sin(Rad), FMath::Cos(Rad), 0);
		Axe->SetAxeVelocity(AxeVelocity * VelocityMultiplyValue);
		Axe->SetPierce(WeaponStatsRow->Pierce);
	}

	SpawnActor->FinishSpawning(SpawnTransform);
}
