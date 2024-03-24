#include "Game/DiaGameSpawner.h"

#include "NavigationSystem.h"
#include "Character/DiaEnemyCharacter.h"
#include "Character/DiaPlayerCharacter.h"
#include "Game/DiaGameState.h"
#include "GameFramework/PlayerState.h"
#include "Containers/Array.h"
#include "Dia/Dia.h"

TArray<TObjectPtr<ADiaEnemyCharacter>> UDiaGameSpawner::SpawnRandom(const FDiaGameModeEnemySpawnData& EnemySpawnData)
{
	return SpawnRandom(EnemySpawnData.WaveEnemies, 1);
}

TArray<TObjectPtr<ADiaEnemyCharacter>> UDiaGameSpawner::SpawnRandom(TArray<TSubclassOf<ADiaEnemyCharacter>> SpawnActors, const int32 SpawnCount)
{
	TArray<TObjectPtr<ADiaEnemyCharacter>> SpawnEnemies;
	if (!DiaGameState)
		return SpawnEnemies;

	for (int i = 0; i < DiaGameState->PlayerArray.Num(); i++)
	{
		if (ADiaPlayerCharacter* DiaCharacter = DiaGameState->PlayerArray[i]->GetPawn<ADiaPlayerCharacter>())
		{
			FNavLocation ResultLocation;
			for (int32 j = 0; j < SpawnCount; j++)
			{
				if (GetRandomReachablePointInCircle(DiaCharacter->GetActorLocation(), 900.f, ResultLocation))
				{
					TSubclassOf<ADiaEnemyCharacter> SpawnCharacterClass = SpawnActors[FMath::RandRange(0, SpawnActors.Num() - 1)];

					FTransform SpawnTransform(ResultLocation);
					ADiaEnemyCharacter* Enemy = GetWorld()->SpawnActorDeferred<ADiaEnemyCharacter>(
						SpawnCharacterClass,
						SpawnTransform,
						nullptr,
						nullptr,
						ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
					);
					Enemy->FinishSpawning(SpawnTransform);
					Enemy->SetTargetActor(DiaCharacter);
					DiaEnemyCharacters.Add(Enemy);

					SpawnEnemies.Add(Enemy);
				}
			}
		}
	}

	return SpawnEnemies;
}

bool UDiaGameSpawner::GetRandomReachablePointInCircle(const FVector& Origin, float Radius, FNavLocation& ResultLocation, ANavigationData* NavData, FSharedConstNavQueryFilter QueryFilter) const
{
	const UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	int32 TryCount = 30;
	while (TryCount-- > 0)
	{
		const float Rad = FMath::FRandRange(0, 2 * UE_PI);
		const FVector Location = Origin + FVector(FMath::Sin(Rad), FMath::Cos(Rad), 0) * Radius;
		FNavLocation Result;
		if (NavigationSystem->GetRandomReachablePointInRadius(Location, 300, Result, NavData, QueryFilter))
		{
			ResultLocation = Result;
			return true;
		}
		else
		{
			UE_LOG(LogDia, Display, TEXT("Try GetRandomReachablePointInCircle [%d].. Circle Rad: %f"), 30 - TryCount, Radius);
		}
	}

	return false;
}

void UDiaGameSpawner::SetEnemySpawnDatas(TArray<FDiaGameModeEnemySpawnData> EnemySpawnDatas)
{
	for (const FDiaGameModeEnemySpawnData& EnemySpawnData : EnemySpawnDatas)
	{
		FTimerHandle TimerHandle;
		// 0이하일 때도 실행하도록 FMath::Max
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			[&, EnemySpawnData]()
			{
				if (EnemySpawnData.bClearAll)
					ClearAllEnemies();

				WaveSpawnTimeInterval = EnemySpawnData.Interval;
				WaveSpawnEnemies = EnemySpawnData.WaveEnemies;
				WaveEnemyMinimum = EnemySpawnData.EnemyMinimum;

				if (EnemySpawnData.SpawnBossDatas.Num() > 0)
				{
					TArray<TSubclassOf<ADiaEnemyCharacter>> EnemyClasses;
					for (FSpawnBossData SpawnBossData : EnemySpawnData.SpawnBossDatas)
						EnemyClasses.Add(SpawnBossData.EnemyClass);
					TArray<TObjectPtr<ADiaEnemyCharacter>> SpawnEnemies = SpawnRandom(EnemyClasses, 1);

					for (int i = 0; i < SpawnEnemies.Num(); i++)
					{
						TObjectPtr<ADiaEnemyCharacter> DiaEnemyCharacter = SpawnEnemies[i];
						FSpawnBossData SpawnBossData = EnemySpawnData.SpawnBossDatas[i];
						DiaEnemyCharacter->SetIsBoss(true);
						DiaEnemyCharacter->SetLevel(SpawnBossData.Level);
					}
				}
			},
			FMath::Max(0.01f, EnemySpawnData.TimeElapsed),
			false);
	}
}

void UDiaGameSpawner::WaveUpdate(float DeltaSeconds)
{
	WaveElapsedTime += DeltaSeconds;

	if (WaveSpawnTimeInterval > WaveElapsedTime)
		return;

	WaveElapsedTime = 0.f;
	if (WaveSpawnEnemies.Num() == 0)
		return;

	// 최소 한개는 뽑는다.
	TArray<TObjectPtr<ADiaEnemyCharacter>> SpawnEnemies = SpawnRandom(WaveSpawnEnemies, FMath::Max(1, WaveEnemyMinimum - SpawnEnemiesSet.Num()));

	// Set으로 Minimum Count를 체크, 삭제 될 때마다 Set에서 삭제. 
	for (const TObjectPtr<ADiaEnemyCharacter> DiaEnemyCharacter : SpawnEnemies)
	{
		DiaEnemyCharacter->OnDestroyed.AddDynamic(this, &UDiaGameSpawner::OnEnemyDestroyed);
	}
	SpawnEnemiesSet.Append(SpawnEnemies);
}

void UDiaGameSpawner::OnEnemyDestroyed(AActor* DestroyedActor)
{
	if (ADiaEnemyCharacter* DiaEnemyCharacter = Cast<ADiaEnemyCharacter>(DestroyedActor))
		SpawnEnemiesSet.Remove(DiaEnemyCharacter);
}

void UDiaGameSpawner::ClearAllEnemies()
{
	for (const TObjectPtr<ADiaEnemyCharacter> DiaEnemyCharacter : SpawnEnemiesSet)
	{
		DiaEnemyCharacter->Destroy();
	}
	
	SpawnEnemiesSet.Empty();
}
