#pragma once

#include "CoreMinimal.h"
#include "Actor/MagnetItem/DiaMagnetItem.h"
#include "Character/DiaCharacterBase.h"
#include "DiaEnemyCharacter.generated.h"

class AAIController;
class UWidgetComponent;
class UBehaviorTree;

USTRUCT(BlueprintType)
struct FDropItemInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ADiaMagnetItem> DropItem;
	UPROPERTY(EditDefaultsOnly)
	float Rarity = 0;
	// 값이 필요할 경우 입력(Gem일 때 Exp값에 대한 정보)
	UPROPERTY(EditDefaultsOnly)
	float Value = 0;

	// MakeTupple을 사용할 건데 TPair의 키는 중복되지 않아야 하므로 중복을 허용하지 않는 타입이어야 함.
	FORCEINLINE bool operator==(FDropItemInfo const& Other) const
	{
		return DropItem == Other.DropItem;
	}

	FORCEINLINE bool operator!=(FDropItemInfo const& Other) const
	{
		return DropItem != Other.DropItem;
	}
};

/**
 * 프로젝트에서 사용된 적들에게 사용된 캐릭터 클래스입니다.
 */
UCLASS()
class DIA_API ADiaEnemyCharacter : public ADiaCharacterBase
{
	GENERATED_BODY()

public:
	ADiaEnemyCharacter();
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void InitAbilitySystem() override;
	virtual void ApplyInitialAttributes() const override;

	virtual int32 GetCharacterLevel_Implementation() const override { return Level; }
	virtual void Die_Implementation() override;

	void SetTargetActor(AActor* TargetActor);

	bool GetIsBoss() const { return bIsBoss; }
	void SetIsBoss(const bool& IsBoss) { bIsBoss = IsBoss; }
	void SetLevel(const int32& InLevel) { Level = InLevel; }

protected:
	UPROPERTY()
	AAIController* AIController;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	int32 Level = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	TSubclassOf<UGameplayEffect> DamageEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	float TimePerDamage = 0.2f;

	float DamageTimer;

	UFUNCTION()
	void OnEnemyHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void OnImcomingDamage(const FOnAttributeChangeData& Data) override;

	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	float DestroyDist = 1600.f;
	// Boss면 삭제하지 않고 근처로 이동시킴
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	bool bIsBoss = false;
	float DestroyDistTimer = 0.f;
	float DestroyDistInterval = 2.f;

	// 멀리 떨어지면 삭제 시킴. Boss면 이동시킴.
	void DistUpdate(float DeltaSeconds);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	TArray<FDropItemInfo> DropItemInfos;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	uint32 DropCount = 1;
	void DropItem();
	void SpawnDropItem(FDropItemInfo DropItem);
};
