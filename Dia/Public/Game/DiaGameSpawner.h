#pragma once

#include "CoreMinimal.h"
#include "Data/DiaGameModeData.h"
#include "NavigationData.h"
#include "DiaGameSpawner.generated.h"

class ADiaGameState;
class ADiaEnemyCharacter;
/**
 * 게임 내에서 Wave등의 의해 Enemy를 Spawn합니다.
 */
UCLASS()
class DIA_API UDiaGameSpawner : public UObject
{
	GENERATED_BODY()

public:
	TArray<TObjectPtr<ADiaEnemyCharacter>> SpawnRandom(const FDiaGameModeEnemySpawnData& EnemySpawnData);
	TArray<TObjectPtr<ADiaEnemyCharacter>> SpawnRandom(TArray<TSubclassOf<ADiaEnemyCharacter>> SpawnActors, int32 SpawnCount);
	void SetDiaGameState(ADiaGameState* InDiaGameState) { DiaGameState = InDiaGameState; }
	bool GetRandomReachablePointInCircle(const FVector& Origin, float Radius, FNavLocation& ResultLocation, ANavigationData* NavData = NULL, FSharedConstNavQueryFilter QueryFilter = NULL) const;
	void SetEnemySpawnDatas(TArray<FDiaGameModeEnemySpawnData> EnemySpawnDatas);

	void WaveUpdate(float DeltaSeconds);
private:
	UPROPERTY()
	ADiaGameState* DiaGameState;
	
	UPROPERTY()
	TArray<TObjectPtr<ADiaEnemyCharacter>> DiaEnemyCharacters;
	TArray<TSubclassOf<ADiaEnemyCharacter>> WaveSpawnEnemies;
	TSet<TObjectPtr<ADiaEnemyCharacter>> SpawnEnemiesSet;
	int32 WaveEnemyMinimum;
	float WaveSpawnTimeInterval = 0.2f;
	float WaveElapsedTime = 0.f;
	
	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);
	void ClearAllEnemies();
};
