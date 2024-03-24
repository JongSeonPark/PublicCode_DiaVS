#include "AbilitySystem/Abilities/Passive/DiaVSAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/Tasks/AbilityTask_Repeat.h"
#include "AbilitySystem/DiaAttributeSet.h"
#include "Character/DiaPlayerCharacter.h"
#include "Components/BoxComponent.h"

void UDiaVSAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	float Time = GetCooldown();
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Duration(Time);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::OnLoopAbility, Time, true);

	if (GameplayEffectToSelfClass)
	{
		UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
		FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		ContextHandle.SetAbility(this);
		GameplayEffectToSelfHandle = AbilitySystemComponent->ApplyGameplayEffectToSelf(GameplayEffectToSelfClass.GetDefaultObject(), GetAbilityLevel(), ContextHandle);
	}
}

void UDiaVSAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (TimerHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	if(GameplayEffectToSelfHandle.IsValid())
	{
		GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(GameplayEffectToSelfHandle);
	}
}

void UDiaVSAbility::AssignDefaultSetByCallerMagnitude(const FGameplayEffectSpecHandle& SpecHandle)
{
	// Super::AssignDefaultSetByCallerMagnitude(SpecHandle);
	if (const FWeaponLevelStatsRow* WeaponStatsRow = GetCurrentLevelWeaponStatsRow())
	{
		if (WeaponStatsRow->Damage > 0 && WeaponStats->DamageTag.IsValid())
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, WeaponStats->DamageTag, WeaponStatsRow->Damage);
	}
	
}

void UDiaVSAbility::OnLoopAbility()
{
	const FWeaponLevelStatsRow* WeaponStatsRow = GetCurrentLevelWeaponStatsRow();
	const int32 SkillAmount = WeaponStatsRow->Amount + GetAmountBonus();
	const float ProjectileInterval = WeaponStatsRow->ProjectileInterval;
	UAbilityTask_Repeat* Repeat = UAbilityTask_Repeat::RepeatAction(this, ProjectileInterval, SkillAmount);
	Repeat->OnPerformAction.AddDynamic(this, &ThisClass::RepeatAction);
	Repeat->Activate();
}

void UDiaVSAbility::RepeatAction(int ActionNumber)
{
}

float UDiaVSAbility::GetSpeedBonus() const
{
	return GetAbilitySystemComponentFromActorInfo()->GetNumericAttribute(UDiaAttributeSet::GetPrimarySpeedAttribute());
}

float UDiaVSAbility::GetSpeed() const
{
	const FWeaponLevelStatsRow* SkillDataRow = GetCurrentLevelWeaponStatsRow();
	float Result = SkillDataRow != nullptr ? SkillDataRow->Speed : 0;
	return Result + GetSpeedBonus();
}

float UDiaVSAbility::GetDurationBonus() const
{
	return GetAbilitySystemComponentFromActorInfo()->GetNumericAttribute(UDiaAttributeSet::GetPrimaryDurationAttribute());
}

float UDiaVSAbility::GetAreaBonus() const
{
	return GetAbilitySystemComponentFromActorInfo()->GetNumericAttribute(UDiaAttributeSet::GetPrimaryAreaAttribute());
}

float UDiaVSAbility::GetCooldownBonus() const
{
	// Cooldown 결과값이 0이하로 갈 수 없도록 최대값 제한
	return FMath::Min(0.9f, GetAbilitySystemComponentFromActorInfo()->GetNumericAttribute(UDiaAttributeSet::GetPrimaryCooldownAttribute()));
}

float UDiaVSAbility::GetAmountBonus() const
{
	return GetAbilitySystemComponentFromActorInfo()->GetNumericAttribute(UDiaAttributeSet::GetPrimaryAmountAttribute());
}

int32 UDiaVSAbility::GetAmount() const
{
	const FWeaponLevelStatsRow* SkillDataRow = GetCurrentLevelWeaponStatsRow();
	int32 Result = SkillDataRow != nullptr ? SkillDataRow->Amount : 0;
	return Result + GetAmountBonus();
}

float UDiaVSAbility::GetCooldown() const
{
	const FWeaponLevelStatsRow* SkillDataRow = GetCurrentLevelWeaponStatsRow();
	float Result = SkillDataRow != nullptr ? SkillDataRow->Cooldown : 1.f;
	Result *= (1 - GetCooldownBonus());
	return Result;
}

float UDiaVSAbility::GetArea() const
{
	const FWeaponLevelStatsRow* SkillDataRow = GetCurrentLevelWeaponStatsRow();
	const float Result = SkillDataRow != nullptr ? SkillDataRow->Area : 1.f;
	return Result + GetAreaBonus();
}

const FWeaponLevelStatsRow* UDiaVSAbility::GetCurrentLevelWeaponStatsRow() const
{
	if (!WeaponStats) return nullptr;
	TArray<FWeaponLevelStatsRow*> OutArray;
	WeaponStats->LevelTable->GetAllRows<FWeaponLevelStatsRow>(TEXT("GetAllRows"), OutArray);
	const int32 Index = GetAbilityLevel() - 1;
	return OutArray.Num() > Index ? OutArray[Index] : nullptr;
}

AActor* UDiaVSAbility::GetNearestEnemy() const
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	TArray<AActor*> OverlappingActors;
	// InAreaBoxComponent에서 Overlap된 Actor들 추출
	if (ADiaPlayerCharacter* PlayerCharacter = Cast<ADiaPlayerCharacter>(AvatarActor))
	{
		PlayerCharacter->GetPlayerLookAreaComponent()->GetOverlappingActors(OverlappingActors, ADiaCharacterBase::StaticClass());
	}
	
	AActor* OverlappingActor = nullptr;
	if (OverlappingActors.Num() > 0)
	{
		// 가장 가까운 적
		float NearestDist = UE_MAX_FLT;
		for (AActor* Actor : OverlappingActors)
		{
			if (Actor == AvatarActor)
				continue;
			
			float DistTemp = FVector::DistSquared2D(Actor->GetActorLocation(), AvatarActor->GetActorLocation());
			if (DistTemp < NearestDist)
			{
				OverlappingActor = Actor;
				NearestDist = DistTemp;
			}
		}
	}

	return OverlappingActor;
}
