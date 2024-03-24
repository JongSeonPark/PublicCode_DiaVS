#include "Player/DiaPlayerState.h"

#include "DiaMathLibrary.h"
#include "AbilitySystem/DiaAbilitySystemComponent.h"
#include "AbilitySystem/DiaAttributeSet.h"
#include "Dia/Dia.h"
#include "Game/DiaGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "UI/Widget/DamageNumberWidgetComponent.h"

ADiaPlayerState::ADiaPlayerState()
{
	/**
	 * ASC가 PlayerState에 있는 경우, PlayerState의 NetUpdateFrequency를 늘려야 합니다.
	 * 기본적으로 PlayerState에서 매우 낮은 값으로 설정되어 있어 클라이언트에서 Attributes 및 GameplayTags등의 변경이 일어나기 전에 지연이 발생하거나 지연이 감지될 수 있습니다.
	 * Adaptive Network Update Frequency를 활성화해야 합니다. 포트나이트가 이를 사용합니다.
	 */
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UDiaAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UDiaAttributeSet>("AttributeSet");
}

void ADiaPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ADiaPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADiaPlayerState, Level);
	DOREPLIFETIME(ADiaPlayerState, Exp);
	DOREPLIFETIME(ADiaPlayerState, LevelUpPoint);
	DOREPLIFETIME(ADiaPlayerState, Gold);
}

void ADiaPlayerState::SetLevel(const int32 InLevel)
{
	Level = InLevel;
	OnLevelChanged.Broadcast(Level);
}

void ADiaPlayerState::SetExp(const int32 InExp)
{
	Exp = InExp;
	OnExpChanged.Broadcast(Exp);
}

void ADiaPlayerState::SetLevelUpPoint(const int32 InLevelUpPoint)
{
	LevelUpPoint = InLevelUpPoint;
	OnLevelUpPointChanged.Broadcast(LevelUpPoint);
}

void ADiaPlayerState::SetGold(const int32 InGold)
{
	Gold = InGold;
	OnGoldChanged.Broadcast(Gold);
}

void ADiaPlayerState::AddLevel(const int32 InLevel)
{
	Level += InLevel;
	OnLevelChanged.Broadcast(Level);
}

void ADiaPlayerState::AddExp(const int32 InExp)
{
	Exp += InExp;
	OnExpChanged.Broadcast(Exp);
}

void ADiaPlayerState::AddLevelUpPoint(const int32 InLevelUpPoint)
{
	LevelUpPoint += InLevelUpPoint;
	OnLevelUpPointChanged.Broadcast(LevelUpPoint);
}

void ADiaPlayerState::AddGold(const int32 InGold)
{
	// Primary Greed Update
	Gold += InGold * (1.f + AttributeSet->GetPrimaryGreed());
	OnGoldChanged.Broadcast(Gold);
}

void ADiaPlayerState::Reset()
{
	UE_LOG(LogDia, Display, TEXT(__FUNCTION__));
	Super::Reset();
}

void ADiaPlayerState::ClientInitialize(AController* C)
{
	UE_LOG(LogDia, Display, TEXT(__FUNCTION__));
	Super::ClientInitialize(C);
}

void ADiaPlayerState::CopyProperties(APlayerState* PlayerState)
{
	UE_LOG(LogDia, Display, TEXT(__FUNCTION__));
	Super::CopyProperties(PlayerState);
}

void ADiaPlayerState::OnDeactivated()
{
	UE_LOG(LogDia, Display, TEXT(__FUNCTION__));
	Super::OnDeactivated();
}

void ADiaPlayerState::OnReactivated()
{
	UE_LOG(LogDia, Display, TEXT(__FUNCTION__));
	Super::OnReactivated();
}

void ADiaPlayerState::OnRep_Level(int32 OldLevel)
{
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("OnRep_Level. OldValue: %d, NewValue: %d"), OldLevel, Level));
	OnLevelChanged.Broadcast(Level);
}

void ADiaPlayerState::OnRep_Exp(int32 OldExp)
{
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("OnRep_Exp. OldValue: %d, NewValue: %d"), OldExp, Exp));
	OnExpChanged.Broadcast(Exp);
}

void ADiaPlayerState::OnRep_LevelUpPoint(int32 OldLevelUpPoint)
{
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("OnRep_LevelUpPoint. OldValue: %d, NewValue: %d"), OldLevelUpPoint, LevelUpPoint));
	// TArray<FGameplayTag> VSTags = GetAvailableRandomVSTags();
	// FString TagsString;
	// for (FGameplayTag Tag : VSTags)
	// {
	// 	TagsString += " " + Tag.ToString();
	// }
	// UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Tags %s"), *TagsString));
	OnLevelUpPointChanged.Broadcast(LevelUpPoint);
}

void ADiaPlayerState::OnRep_Gold(int32 OldGold)
{
	OnGoldChanged.Broadcast(OldGold);
}

TArray<FGameplayTag> ADiaPlayerState::GetRandomVSTagsOnLevelUp(int32 NumSelections) const
{
	TArray<FGameplayTag> Result;
	// FGameplay와 Rarity
	TArray<TPair<FGameplayTag, float>> TagAndRarity;
	UDiaGameInstance* DiaGameInstance = GetWorld()->GetGameInstance<UDiaGameInstance>();
	if (!DiaGameInstance) return Result;

	TMap<FGameplayTag, FGameplayAbilitySpecHandle> AbilitySpecHandles = AbilitySystemComponent->GetVSGameplayAbilitySpecHandles();


	if (AbilitySpecHandles.Num() < 6)
	{
		for (TTuple<FGameplayTag, TObjectPtr<UWeaponStats>> WeaponStatsData : DiaGameInstance->GetWeaponStatsDatas())
		{
			FGameplayTag Tag = WeaponStatsData.Key;
			TObjectPtr<UWeaponStats> WeaponStats = WeaponStatsData.Value;

			if (AbilitySpecHandles.Contains(Tag))
			{
				FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(AbilitySpecHandles[Tag]);
				// 현재 최대레벨이면 제외
				if (AbilitySpec->Level >= WeaponStats->GetMaxLevel())
					continue;
			}
			TagAndRarity.Add(MakeTuple(Tag, WeaponStats->Rarity));
		}
	}
	else
	{
		// 꽉차면 레벨 덜 찬 것만 진행
		for (TTuple<FGameplayTag, FGameplayAbilitySpecHandle> AbilitySpecHandle : AbilitySpecHandles)
		{
			FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(AbilitySpecHandle.Value);
			TObjectPtr<UWeaponStats> WeaponStats = DiaGameInstance->GetWeaponStatsDatas()[AbilitySpecHandle.Key];
			if (AbilitySpec->Level < WeaponStats->GetMaxLevel())
			{
				TagAndRarity.Add(MakeTuple(AbilitySpecHandle.Key, WeaponStats->Rarity));
			}
		}
	}

	// 현재 가지고 있는 VS Effect(PassiveItem)
	TMap<FGameplayTag, FActiveGameplayEffectHandle> ActiveGameplayEffectHandles = AbilitySystemComponent->GetVSGameplayEffectHandles();

	if (ActiveGameplayEffectHandles.Num() < 6)
	{
		for (TTuple<FGameplayTag, TObjectPtr<UPassiveItemStats>> PassiveItemStatsData : DiaGameInstance->GetPassiveItemStatsDatas())
		{
			FGameplayTag Tag = PassiveItemStatsData.Key;
			TObjectPtr<UPassiveItemStats> ItemStats = PassiveItemStatsData.Value;
			if (ActiveGameplayEffectHandles.Contains(Tag))
			{
				const FActiveGameplayEffect* ActiveEffect = AbilitySystemComponent->GetActiveGameplayEffect(ActiveGameplayEffectHandles[Tag]);
				// 현재 최대레벨이면 제외
				if (ActiveEffect->Spec.GetLevel() >= ItemStats->GetMaxLevel())
					continue;
			}
			TagAndRarity.Add(MakeTuple(Tag, ItemStats->Rarity));
		}
	}
	else
	{
		// 꽉차면 레벨 덜 찬 것만 진행
		for (TTuple<FGameplayTag, FActiveGameplayEffectHandle> ActiveGameplayEffectHandle : ActiveGameplayEffectHandles)
		{
			const FActiveGameplayEffect* ActiveEffect = AbilitySystemComponent->GetActiveGameplayEffect(ActiveGameplayEffectHandle.Value);
			TObjectPtr<UPassiveItemStats> PassiveStats = DiaGameInstance->GetPassiveItemStatsDatas()[ActiveGameplayEffectHandle.Key];
			if (ActiveEffect->Spec.GetLevel() < PassiveStats->GetMaxLevel())
			{
				TagAndRarity.Add(MakeTuple(ActiveGameplayEffectHandle.Key, PassiveStats->Rarity));
			}
		}
	}

	// 뽑을 수가 더 많으면 전부 리턴.
	if (NumSelections >= TagAndRarity.Num())
	{
		for (TTuple<FGameplayTag, float> TagRarity : TagAndRarity)
		{
			Result.Add(TagRarity.Key);
		}
	}
	else
	{
		// 가중치 계산
		TArray<TTuple<FGameplayTag, float>> SelectedTags = UDiaMathLibrary::WeightedRandomSelection(TagAndRarity, true, NumSelections);
		for (TTuple<FGameplayTag, float> TagRarity : SelectedTags)
		{
			Result.Add(TagRarity.Key);
		}
	}

	return Result;
}

TArray<FGameplayTag> ADiaPlayerState::GetRandomVSTagsWhenOpeningTreasureChest(int32 NumSelections, OUT TArray<FGameplayTag>& RemoveTags) const
{
	TArray<FGameplayTag> Result;
	TArray<TPair<FGameplayTag, float>> TagAndRarity;
	UDiaGameInstance* DiaGameInstance = GetWorld()->GetGameInstance<UDiaGameInstance>();
	if (!DiaGameInstance) return Result;

	// 현재 가지고 있는 VS Ability
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> AbilitySpecHandles = AbilitySystemComponent->GetVSGameplayAbilitySpecHandles();
	// 현재 가지고 있는 VS Effect(PassiveItem)
	TMap<FGameplayTag, FActiveGameplayEffectHandle> ActiveGameplayEffectHandles = AbilitySystemComponent->GetVSGameplayEffectHandles();

	// Weapon Check
	for (TPair<FGameplayTag, FGameplayAbilitySpecHandle> AbilitySpecHandlePair : AbilitySpecHandles)
	{
		FGameplayTag VSTag = AbilitySpecHandlePair.Key;
		FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(AbilitySpecHandlePair.Value);

		// 레벨업 할 수 있는 수만큼 TagAndRarity에 Add
		// 중복확률을 낮추기 위해 첫번째 이후로 확률을 낮춤.
		float DivideProbability = 1.f;
		for (int i = AbilitySpec->Level; i < DiaGameInstance->GetWeaponStatsDatas()[VSTag]->GetMaxLevel(); i++)
		{
			TagAndRarity.Add(MakeTuple(VSTag, DiaGameInstance->GetWeaponStatsDatas()[VSTag]->Rarity / DivideProbability));
			DivideProbability += 1.f;
		}
	}

	// Passive Item Check
	for (TPair<FGameplayTag, FActiveGameplayEffectHandle> ActiveGameplayEffectHandlePair : ActiveGameplayEffectHandles)
	{
		const FActiveGameplayEffect* ActiveEffect = AbilitySystemComponent->GetActiveGameplayEffect(ActiveGameplayEffectHandlePair.Value);
		TObjectPtr<UPassiveItemStats> PassiveStats = DiaGameInstance->GetPassiveItemStatsDatas()[ActiveGameplayEffectHandlePair.Key];

		// 레벨업 할 수 있는 수만큼 TagAndRarity에 Add
		// 중복확률을 낮추기 위해 첫번째 이후로 확률을 낮춤.
		float DivideProbability = 1.f;
		for (int i = ActiveEffect->Spec.GetLevel(); i < PassiveStats->GetMaxLevel(); i++)
		{
			TagAndRarity.Add(MakeTuple(ActiveGameplayEffectHandlePair.Key, PassiveStats->Rarity / DivideProbability));
			DivideProbability += 1.f;
		}
	}

	// Evolution Check
	for (TPair<FGameplayTag, FItemEvolutionInfo> EvoulutionInfoPair : DiaGameInstance->GetEvoulutionInfos())
	{
		FItemEvolutionInfo ItemEvolutionInfo = EvoulutionInfoPair.Value;
		bool bCanEvoultion = true;

		// Evolution 가능한지 체크
		for (TPair<FGameplayTag, int32> RequireTagAndLevel : ItemEvolutionInfo.RequireTagAndLevel)
		{
			FGameplayTag VSTag = RequireTagAndLevel.Key;
			int32 RequireLevel = RequireTagAndLevel.Value;
			if (DiaGameInstance->GetWeaponStatsDatas().Contains(VSTag))
			{
				if (AbilitySpecHandles.Contains(VSTag))
				{
					FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(AbilitySpecHandles[VSTag]);
					if (AbilitySpec->Level < RequireLevel)
					{
						bCanEvoultion = false;
						break;
					}
				}
				else
				{
					bCanEvoultion = false;
					break;
				}
			}
			else if (DiaGameInstance->GetPassiveItemStatsDatas().Contains(VSTag))
			{
				if (ActiveGameplayEffectHandles.Contains(VSTag))
				{
					const FActiveGameplayEffect* ActiveEffect = AbilitySystemComponent->GetActiveGameplayEffect(ActiveGameplayEffectHandles[VSTag]);
					if (ActiveEffect->Spec.GetLevel() < RequireLevel)
					{
						bCanEvoultion = false;
						break;
					}
				}
				else
				{
					bCanEvoultion = false;
					break;
				}
			}
		}

		if (bCanEvoultion)
		{
			TagAndRarity.Add(MakeTuple(EvoulutionInfoPair.Key, ItemEvolutionInfo.Rarity));
		}
	}

	// 가중치 계산
	TArray<TTuple<FGameplayTag, float>> SelectedTags = UDiaMathLibrary::WeightedRandomSelection(TagAndRarity, true, NumSelections);

	// 업그레이드 할게 없다면 나머지를 coin으로 채움
	for (int32 i = 0; i < NumSelections; i++)
	{
		if (SelectedTags.Num() > i)
		{
			Result.Add(SelectedTags[i].Key);
			// Evolution Item일시 재료 삭제
			if (DiaGameInstance->GetEvoulutionInfos().Contains(SelectedTags[i].Key))
			{
				RemoveTags.Append(DiaGameInstance->GetEvoulutionInfos()[SelectedTags[i].Key].RemoveItemTags);
			}
		}
		else
		{
			Result.Add(DiaGameplayTags::Pickup_GoldCoin);
		}
	}

	return Result;
}

void ADiaPlayerState::OnDamageNumberMessage_Client_Implementation(AActor* Target, float Damage)
{
	if (DamageNumberWidgetCompClass && Target)
	{
		UDamageNumberWidgetComponent* DamageText = NewObject<UDamageNumberWidgetComponent>(Target, DamageNumberWidgetCompClass);
		// NewObject로 생성했으니 RegisterComponent 호출..
		DamageText->RegisterComponent();
		// 위치 잡기 위해 붙였다가 바로 Detach
		DamageText->AttachToComponent(Target->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(Damage);
	}
}

void ADiaPlayerState::OnTreasureChestOpen_Client_Implementation(const TArray<FGameplayTag>& ItemTags)
{
	OnTreasureChestOpened.Broadcast(ItemTags);
}
