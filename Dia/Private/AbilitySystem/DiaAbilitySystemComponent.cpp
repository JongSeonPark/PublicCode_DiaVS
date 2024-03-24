#include "AbilitySystem/DiaAbilitySystemComponent.h"

#include "DiaGameplayTags.h"
#include "Data/DiaVSItemDatas.h"
#include "Dia/Dia.h"
#include "Game/DiaGameInstance.h"

void UDiaAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UDiaAbilitySystemComponent::OnActiveGameplayEffectAddedToSelf);
	OnAnyGameplayEffectRemovedDelegate().AddUObject(this, &UDiaAbilitySystemComponent::OnAnyGameplayEffectRemoved);
}

void UDiaAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);

	const FGameplayTagContainer VSTagContainer = AbilitySpec.Ability->AbilityTags.Filter(FGameplayTagContainer(DiaGameplayTags::Ability_VS));
	// 있다면 아마 하나만 넣을 것
	for (FGameplayTag VSTag : VSTagContainer)
		VSGameplayAbilitySpecHandles.Add(VSTag, AbilitySpec.Handle);
}

void UDiaAbilitySystemComponent::OnRemoveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnRemoveAbility(AbilitySpec);

	const FGameplayTagContainer VSTagContainer = AbilitySpec.Ability->AbilityTags.Filter(FGameplayTagContainer(DiaGameplayTags::Ability_VS));
	// 있다면 아마 하나만 삭제
	for (FGameplayTag VSTag : VSTagContainer)
		VSGameplayAbilitySpecHandles.Remove(VSTag);
}

void UDiaAbilitySystemComponent::OnActiveGameplayEffectAddedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT(__FUNCTION__), true, true, FColor::Blue, 5.f);
	
	FGameplayTagContainer AssetTags;
	EffectSpec.GetAllAssetTags(AssetTags);
	// 설계상 아마 1개 들어올 것임
	for (FGameplayTag VSTag : AssetTags.Filter(FGameplayTagContainer(DiaGameplayTags::Effect_VS_Passive)))
	{
		VSGameplayEffectHandles.Add(VSTag, ActiveGameplayEffectHandle);
	}
}

void UDiaAbilitySystemComponent::OnAnyGameplayEffectRemoved(const FActiveGameplayEffect& ActiveGameplayEffect)
{
	//UKismetSystemLibrary::PrintString(GetWorld(), TEXT(__FUNCTION__), true, true, FColor::Blue, 5.f);
	FGameplayEffectSpec EffectSpec = ActiveGameplayEffect.Spec;
	FGameplayTagContainer AssetTags;
	EffectSpec.GetAllAssetTags(AssetTags);
	// 설계상 아마 1개 들어올 것임
	for (FGameplayTag VSTag : AssetTags.Filter(FGameplayTagContainer(DiaGameplayTags::Effect_VS_Passive)))
	{
		VSGameplayEffectHandles.Remove(VSTag);
	}
}

int32 UDiaAbilitySystemComponent::GetVSItemLevel(FGameplayTag VSTag) const
{
	if (VSGameplayAbilitySpecHandles.Contains(VSTag))
	{
		const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(VSGameplayAbilitySpecHandles[VSTag]);
		return AbilitySpec->Level;
	}
	if (VSGameplayEffectHandles.Contains(VSTag))
	{
		const FActiveGameplayEffect* ActiveEffect = GetActiveGameplayEffect(VSGameplayEffectHandles[VSTag]);
		return ActiveEffect->Spec.GetLevel();		
	}

	return 0;
}

void UDiaAbilitySystemComponent::AddAbilityLevel_Server_Implementation(TSubclassOf<UGameplayAbility> GameplayAbilityClass, int32 AddLevel)
{
	TArray<FGameplayAbilitySpecHandle> OutAbilitySpecHandles;
	// VS Ability는 1개만 있을 것이라 가정하겠음.
	const FGameplayTagContainer VSTagContainer = GameplayAbilityClass.GetDefaultObject()->AbilityTags.Filter(FGameplayTagContainer(DiaGameplayTags::Ability_VS));
	FindAllAbilitiesWithTags(OutAbilitySpecHandles, VSTagContainer);
	UWorld* World = GetWorld();

	// 기존 Ability를 가지고 있다면 레벨 업그레이드
	// 없으면 Ability를 생성
	if (World && OutAbilitySpecHandles.Num() > 0)
	{
		const UDiaGameInstance* DiaGameInstance = World->GetGameInstance<UDiaGameInstance>();
		const TMap<FGameplayTag, TObjectPtr<UWeaponStats>>& WeaponStatsDatas = DiaGameInstance ? DiaGameInstance->GetWeaponStatsDatas() : TMap<FGameplayTag, TObjectPtr<UWeaponStats>>();
		for (const FGameplayAbilitySpecHandle AbilitySpecHandle : OutAbilitySpecHandles)
		{
			FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(AbilitySpecHandle);
			int32 LevelTemp = AbilitySpec->Level + AddLevel;
			// VSTagContainer에 1개만 있다는 가정.
			if (const TObjectPtr<UWeaponStats> WeaponStats = WeaponStatsDatas[VSTagContainer.First()])
			{
				if (WeaponStats->GetMaxLevel() == AbilitySpec->Level)
				{
					UE_LOG(LogDia, Warning, TEXT("%s is MaxLevel. CurrentLevel: %d, MaxLevel: %d"), *AbilitySpec->Ability->GetName(), AbilitySpec->Level, WeaponStats->GetMaxLevel());
					break;
				}

				if (WeaponStats->GetMaxLevel() < AbilitySpec->Level + AddLevel)
				{
					UE_LOG(LogDia, Warning, TEXT("%s Level exceed. CurrentLevel: %d, MaxLevel: %d"), *AbilitySpec->Ability->GetName(), AbilitySpec->Level, WeaponStats->GetMaxLevel());
					LevelTemp = WeaponStats->GetMaxLevel();
				}
			}
			AbilitySpec->Level = LevelTemp;
			UE_LOG(LogDia, Display, TEXT("%s Level: %d"), *AbilitySpec->Ability->GetName(), AbilitySpec->Level);
			MarkAbilitySpecDirty(*AbilitySpec);
		}
	}
	else
	{
		const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(GameplayAbilityClass, FMath::Max(1, AddLevel));
		GiveAbility(AbilitySpec);
		UE_LOG(LogDia, Display, TEXT("%s added. Level: %d"), *AbilitySpec.Ability->GetName(), AbilitySpec.Level);
	}
}

void UDiaAbilitySystemComponent::AddEffectLevel_Server_Implementation(TSubclassOf<UGameplayEffect> GameplayEffectClass, int32 AddLevel)
{
	const UGameplayEffect* GameplayEffectDefault = GameplayEffectClass->GetDefaultObject<UGameplayEffect>();
	const FGameplayTagContainer GrantedVSTags = GameplayEffectDefault->GetAssetTags().Filter(FGameplayTagContainer(DiaGameplayTags::Effect_VS_Passive));
	const FGameplayTag GameplayEffectVSTag = GrantedVSTags.First(); // Effect_VS Tag를 하나만 가지고 있다고 가정.
	// VS Effect Tag가 아니면 리턴 
	if (!GameplayEffectVSTag.IsValid()) return;

	const UWorld* World = GetWorld();
	const UDiaGameInstance* DiaGameInstance = World->GetGameInstance<UDiaGameInstance>();
	// DiaGameInstance가 아니면 리턴 
	if (!DiaGameInstance) return;
	const TMap<FGameplayTag, TObjectPtr<UPassiveItemStats>>& PassiveItemStatsDatas = DiaGameInstance->GetPassiveItemStatsDatas();
	const TObjectPtr<UPassiveItemStats> PassiveItemStats = PassiveItemStatsDatas[GameplayEffectVSTag];

	TArray<FActiveGameplayEffectHandle> ActiveGameplayEffectHandles = GetActiveEffectsWithAllTags(FGameplayTagContainer(GrantedVSTags));

	// 없으면 하나 적용.
	if (ActiveGameplayEffectHandles.Num() == 0)
	{
		const FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext();
		const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(GameplayEffectClass, AddLevel, EffectContextHandle);
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		UE_LOG(LogDia, Display, TEXT("%s added. Level: %f"), *GameplayEffectClass->GetName(), EffectSpecHandle.Data->GetLevel());
		return;
	}

	// 레벨업
	for (const FActiveGameplayEffectHandle Handle : ActiveGameplayEffectHandles)
	{
		const FActiveGameplayEffect* ActiveEffect = GetActiveGameplayEffect(Handle);
		const int32 NewLevel = PassiveItemStats ? FMath::Min(PassiveItemStats->MaxLevel, ActiveEffect->Spec.GetLevel() + AddLevel) : ActiveEffect->Spec.GetLevel() + AddLevel;
		UE_LOG(LogDia, Display, TEXT("%s Level: %d"), *GetGameplayEffectCDO(Handle)->GetName(), NewLevel);
		SetActiveGameplayEffectLevel(Handle, NewLevel);
	}
}

void UDiaAbilitySystemComponent::RemoveVSAbility_Server_Implementation(FGameplayTag VSTag)
{
	if (VSGameplayAbilitySpecHandles.Contains(VSTag))
	{
		ClearAbility(VSGameplayAbilitySpecHandles[VSTag]);
		VSGameplayAbilitySpecHandles.Remove(VSTag);
	}
}

void UDiaAbilitySystemComponent::RemoveVSEffect_Server_Implementation(FGameplayTag VSTag)
{
	if (VSGameplayEffectHandles.Contains(VSTag))
	{
		RemoveActiveGameplayEffect(VSGameplayEffectHandles[VSTag]);
		VSGameplayEffectHandles.Remove(VSTag);
	}
}
