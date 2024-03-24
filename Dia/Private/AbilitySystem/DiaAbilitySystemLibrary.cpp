#include "AbilitySystem/DiaAbilitySystemLibrary.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystem/DiaAbilitySystemComponent.h"
#include "Actor/DiaSkillObject.h"
#include "Character/DiaPlayerCharacter.h"
#include "Game/DiaGameInstance.h"
#include "Player/DiaPlayerState.h"

void UDiaAbilitySystemLibrary::AssignSetByCallerMagnitudes(const FGameplayEffectSpecHandle& SpecHandle, const TMap<FGameplayTag, FScalableFloat> DefaultSetByCallerTypes, const float Level)
{
	for (const TTuple<FGameplayTag, FScalableFloat> Pair : DefaultSetByCallerTypes)
	{
		const FGameplayTag Tag = Pair.Key;
		FScalableFloat ScalableFloat = Pair.Value;
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Tag, ScalableFloat.GetValueAtLevel(Level));
	}
}

TArray<FTransform> UDiaAbilitySystemLibrary::GetCircleAroundTransforms(const int Count, const float Radius)
{
	TArray<FTransform> Result;
	for (int32 i = 0; i < Count; i++)
	{
		const float Rad = (2 * PI / Count) * i;
		FTransform Trans;
		const FVector Location = FVector(FMath::Sin(Rad), FMath::Cos(Rad), 0) * Radius;
		Trans.SetLocation(Location);
		Trans.SetRotation(Location.Rotation().Quaternion());
		Result.Add(Trans);
	}
	return Result;
}

AActor* UDiaAbilitySystemLibrary::SpawnActorFromAbility(UDiaGameplayAbility* Ability, TSubclassOf<ADiaSkillObject> SpawnActorClass, TSubclassOf<UGameplayEffect> GameplayEffectClass, const FTransform& SpawnTransform, bool bIsFinishSpawning)
{
	AActor* AvatarActor = Ability->GetAvatarActorFromActorInfo();
	const UAbilitySystemComponent* AbilitySystemComponent = Ability->GetAbilitySystemComponentFromActorInfo();

	UWorld* World = GEngine->GetWorldFromContextObject(Ability, EGetWorldErrorMode::LogAndReturnNull);

	ADiaSkillObject* SpawnActor = World->SpawnActorDeferred<ADiaSkillObject>(
		SpawnActorClass,
		SpawnTransform,
		AvatarActor,
		Cast<APawn>(AvatarActor));

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.SetAbility(Ability);
	EffectContextHandle.AddSourceObject(SpawnActor);

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Ability->GetAbilityLevel(), EffectContextHandle);
	Ability->AssignDefaultSetByCallerMagnitude(SpecHandle);
	SpawnActor->SetEffectSpecHandle(SpecHandle);

	if (bIsFinishSpawning)
		SpawnActor->FinishSpawning(SpawnTransform);

	return SpawnActor;
}

void UDiaAbilitySystemLibrary::AddVSItemLevel_Server(UDiaAbilitySystemComponent* AbilitySystemComponent, FGameplayTag VSGameplayTag, int32 AddLevel)
{
	UWorld* World = GEngine->GetWorldFromContextObject(AbilitySystemComponent, EGetWorldErrorMode::LogAndReturnNull);

	// LevelUp 포인트를 1개 제거
	if (ADiaPlayerCharacter* DiaPlayerCharacter = Cast<ADiaPlayerCharacter>(AbilitySystemComponent->GetAvatarActor()))
	{
		DiaPlayerCharacter->GetPlayerState<ADiaPlayerState>()->AddLevelUpPoint(-1);
	}
	
	if(UDiaGameInstance* DiaGameInstance = World->GetGameInstance<UDiaGameInstance>())
	{
		if (DiaGameInstance->GetWeaponStatsDatas().Contains(VSGameplayTag))
		{
			TObjectPtr<UWeaponStats> WeaponStats = DiaGameInstance->GetWeaponStatsDatas()[VSGameplayTag];
			AbilitySystemComponent->AddAbilityLevel_Server(WeaponStats->GameplayAbilityClass, AddLevel);
			return;
		}
		if (DiaGameInstance->GetPassiveItemStatsDatas().Contains(VSGameplayTag))
		{
			TObjectPtr<UPassiveItemStats> PassiveItemStats = DiaGameInstance->GetPassiveItemStatsDatas()[VSGameplayTag];
			AbilitySystemComponent->AddEffectLevel_Server(PassiveItemStats->GameplayEffectClass, AddLevel);
		}
	}
}

UDiaAbilitySystemComponent* UDiaAbilitySystemLibrary::GetAbilitySystemComponent(AActor* Actor)
{
	return Cast<UDiaAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor));
}
