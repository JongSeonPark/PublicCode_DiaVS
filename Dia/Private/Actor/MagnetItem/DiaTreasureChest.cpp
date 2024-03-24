#include "Actor/MagnetItem/DiaTreasureChest.h"

#include "DiaMathLibrary.h"
#include "Character/DiaPlayerCharacter.h"
#include "Game/DiaGameInstance.h"
#include "Player/DiaPlayerState.h"

// 나올 확률표
const TArray<TPair<int, float>> ADiaTreasureChest::TreasureCountAndRarity = {
	MakeTuple(6, 0.1f),
	MakeTuple(3, 0.2f),
	MakeTuple(1, 0.7f),
};

void ADiaTreasureChest::AcceptedActorUpdate(AActor* CollisionActor)
{
	const ADiaPlayerCharacter* DiaPlayerCharacter = Cast<ADiaPlayerCharacter>(CollisionActor);
	if (!DiaPlayerCharacter) return;
	ADiaPlayerState* DiaPlayerState = DiaPlayerCharacter->GetPlayerState<ADiaPlayerState>();
	if (!DiaPlayerState) return;
	const UDiaGameInstance* DiaGameInstance = GetGameInstance<UDiaGameInstance>();
	if (!DiaGameInstance) return;

	int32 TreasureCount = ComputeTreasureCount();

	// Evoultion 아이템으로 인한 삭제
	TArray<FGameplayTag> RemoveTags;
	TArray<FGameplayTag> TreasureTags = DiaPlayerState->GetRandomVSTagsWhenOpeningTreasureChest(TreasureCount, RemoveTags);

	for (FGameplayTag ItemTag : TreasureTags)
	{
		if (const UItemStatsBase* ItemStats = DiaGameInstance->GetItemStats(ItemTag))
		{
			switch (ItemStats->GetItemType())
			{
			case EVSItemType::Weapon:
				DiaPlayerCharacter->GetDiaAbilitySystemComponent()->AddAbilityLevel_Server(Cast<UWeaponStats>(ItemStats)->GameplayAbilityClass);
				break;
			case EVSItemType::Passive:
				DiaPlayerCharacter->GetDiaAbilitySystemComponent()->AddEffectLevel_Server(Cast<UPassiveItemStats>(ItemStats)->GameplayEffectClass);
				break;
			}
		}
		else if (ItemTag.MatchesTagExact(DiaGameplayTags::Pickup_GoldCoin))
		{
			DiaPlayerState->AddGold(25);
		}
	}

	for (FGameplayTag RemoveTag : RemoveTags)
	{
		if (const UItemStatsBase* ItemStats = DiaGameInstance->GetItemStats(RemoveTag))
		{
			switch (ItemStats->GetItemType())
			{
			case EVSItemType::Weapon:
				DiaPlayerCharacter->GetDiaAbilitySystemComponent()->RemoveVSAbility_Server(ItemStats->Tag);
				break;
			case EVSItemType::Passive:
				DiaPlayerCharacter->GetDiaAbilitySystemComponent()->RemoveVSEffect_Server(ItemStats->Tag);
				break;
			}
		}
	}

	DiaPlayerState->OnTreasureChestOpen_Client(TreasureTags);
}

int32 ADiaTreasureChest::ComputeTreasureCount() const
{
	return UDiaMathLibrary::WeightedRandomSelection(TreasureCountAndRarity, false, 1)[0].Key;
}
