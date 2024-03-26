

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DiaGameModeData.generated.h"

class ADiaEnemyCharacter;

UENUM(BlueprintType)
enum class ESpawnEvent : uint8
{
	Wave, // 현재 소환하는  Enemy들을 지정한다.
	Circle, // Circle로 감싸는 모습
	Map, // 한 부분에서 무더기로 소환
	Boss, // Boss 한 마리 소환 
};

/**
 * 보스 캐릭터 스폰용 데이터입니다.
 */
USTRUCT(BlueprintType)
struct FSpawnBossData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADiaEnemyCharacter> EnemyClass;
	UPROPERTY(EditDefaultsOnly)
	int32 Level = 1;
	UPROPERTY(EditDefaultsOnly)
	bool bHasEvolution = true;
};

/**
 * GameMode의 GameSpawner에서 Enemy들에 대한 스폰 정보입니다.
 */
USTRUCT(BlueprintType)
struct FDiaGameModeEnemySpawnData
{
	GENERATED_BODY()
	// 발생 시간
	UPROPERTY(EditDefaultsOnly)
	double TimeElapsed = 0.f;

	// Wave에서 사용
	UPROPERTY(EditDefaultsOnly)
	double Interval = 1.0;
	UPROPERTY(EditDefaultsOnly)
	int32 EnemyMinimum = 15;
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ADiaEnemyCharacter>> WaveEnemies;

	// BossSpawn
	UPROPERTY(EditDefaultsOnly)
	TArray<FSpawnBossData> SpawnBossDatas;

	// 현 시간에 다른 몬스터를 모두 삭제할 것인지
	UPROPERTY(EditDefaultsOnly)
	bool bClearAll = false;	
};

/**
 * DiaGameMode에서 저장됩니다. 각자의 스테이지(Map, Level)에서 사용될 정보입니다.
 */
UCLASS()
class DIA_API UDiaGameModeData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FDiaGameModeEnemySpawnData> EnemySpawnDatas;
};

UCLASS(BlueprintType)
class DIA_API UDiaStageInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Info;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Texture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> Level;
};
