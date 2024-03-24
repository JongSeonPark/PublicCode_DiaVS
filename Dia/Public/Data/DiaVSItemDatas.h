#pragma once

#include "CoreMinimal.h"
#include "DiaGameplayTags.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "DiaVSItemDatas.generated.h"

UENUM(BlueprintType)
enum class EVSItemType : uint8
{
	Weapon, // 무기(Axe, Knife등)
	Passive, // 패시브 아이템(Hollow Heart, Wings 등) 
};

USTRUCT(BlueprintType)
struct FItemStatsRow : public FTableRowBase
{
	GENERATED_BODY()
	// 아이템이 레벨업시 얻게 될 정보 표시
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Info")
	FText LevelupInfo;
};

/**
 * 레벨에 따른 Weapon 정보
 * 0번 Row가 1레벨
 */
USTRUCT(BlueprintType)
struct FWeaponLevelStatsRow : public FItemStatsRow
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	float Damage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	float Area = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	float Speed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	int32 Amount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	float Duration = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	int32 Pierce = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	float Cooldown = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	float ProjectileInterval = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	float Chance = 0;
};

/**
 * VS Item(Axe 등의 무기나 Spinach등의 패시브 아이템)의 대한 정보입니다.
 */
UCLASS(BlueprintType)
class DIA_API UItemStatsBase : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	FGameplayTag Tag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	UTexture2D* Texture;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	int32 Rarity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	UDataTable* LevelTable;

	UFUNCTION(BlueprintCallable)
	virtual int32 GetMaxLevel() const { return 0; }

	UFUNCTION(BlueprintCallable)
	virtual EVSItemType GetItemType() const { return EVSItemType::Weapon; }

	UFUNCTION(BlueprintCallable)
	FText GetLevelupInfoText(int32 Level)
	{
		TArray<FItemStatsRow*> OutArray;
		LevelTable->GetAllRows<FItemStatsRow>(TEXT("GetAllRows"), OutArray);
		const int32 Index = FMath::Max(0, Level - 1);
		return OutArray[Index]->LevelupInfo;
	}
};

/**
 * DiaGameInstance에 저장될 무기 정보입니다.
 */
UCLASS()
class DIA_API UWeaponStats : public UItemStatsBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats", meta = (Categories="Damage"))
	FGameplayTag DamageTag = DiaGameplayTags::Damage_Melee;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	int32 PoolLimit = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	bool BlockByWalls = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	float HitboxDelay = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	float Knockback = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponStats")
	float CritMulti = 0;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponStats")
	TSubclassOf<class UGameplayAbility> GameplayAbilityClass;

	/**
	 * 1개 있으면 1이 MaxLevel.
	 * -1이면 데이터 없음.
	 * @return LevelTable Num() 
	 */
	virtual int32 GetMaxLevel() const override { return LevelTable ? LevelTable->GetRowMap().Num() : -1; }
	virtual EVSItemType GetItemType() const override { return EVSItemType::Weapon; }
};

/**
 * DiaGameInstance에 저장될 패시브 아이템 정보입니다.
 */
UCLASS()
class DIA_API UPassiveItemStats : public UItemStatsBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PassiveItemStats")
	int32 MaxLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PassiveItemStats")
	TSubclassOf<class UGameplayEffect> GameplayEffectClass;

	virtual int32 GetMaxLevel() const override { return MaxLevel; }
	virtual EVSItemType GetItemType() const override { return EVSItemType::Passive; }
};

/**
 * 조합 아이템 정보입니다.
 */
USTRUCT(BlueprintType)
struct DIA_API FItemEvolutionInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EvolutionInfo")
	TMap<FGameplayTag, int32> RequireTagAndLevel;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EvolutionInfo")
	TArray<FGameplayTag> RemoveItemTags;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EvolutionInfo")
	FGameplayTag RewardTag;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EvolutionInfo")
	int32 Rarity = 200;
};
