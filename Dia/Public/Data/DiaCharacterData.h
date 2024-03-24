

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DiaCharacterData.generated.h"

/**
 * 캐릭터 선택 시, 초기값에 대한 Attribute를 설정하기 위해 사용한 DataAsset입니다.
 */
UCLASS()
class DIA_API UDiaCharacterData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float MaxHealth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float HealthRegeneration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float Armor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float MoveSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float Might;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float Speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float Duration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float Area;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float Cooldown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float Amount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float Revival;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float Magnet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float Luck;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float Growth;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float Greed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	float Curse;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character, meta = (Categories="Ability.VS.Weapon"))
	FGameplayTag WeaponTag;
	
};

/**
 * DiaameInstance에서 캐릭터 정보를 저장하기 위해 사용되었습니다.
 */
UCLASS(BlueprintType)
class DIA_API UDiaCharacterInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	FText Info;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	UTexture2D* Texture;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character)
	TSubclassOf<class ADiaPlayerCharacter> CharacterClass;
};

