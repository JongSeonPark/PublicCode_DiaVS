#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/DiaAbilitySystemComponent.h"
#include "AbilitySystem/DiaAttributeSet.h"
#include "UI/Widget/DamageNumberWidgetComponent.h"
#include "DiaPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTreasureChestOpened, TArray<FGameplayTag>);

/**
 * 본 프로젝트에서는 AbilitySystemComponent, AttributeSet를 여기서 생성한다.
 *	- Character에서 하지 않는 이유는 Revival로 인해 Character가 재생성될 여지가 있음.
 *
 * 그 외 캐릭터에 종속 되지 않는 값(골드 및 경험치 등)은 PlayerState에서 Replicated하여 관리.
 */
UCLASS()
class DIA_API ADiaPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ADiaPlayerState();
	virtual void BeginPlay() override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UDiaAttributeSet* GetAttributeSet() const { return AttributeSet; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FOnPlayerStatChanged OnExpChanged;
	FOnPlayerStatChanged OnLevelChanged;
	FOnPlayerStatChanged OnLevelUpPointChanged;
	FOnPlayerStatChanged OnGoldChanged;
	
	FOnTreasureChestOpened OnTreasureChestOpened;

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE int32 GetExp() const { return Exp; }
	FORCEINLINE int32 GetLevelUpPoint() const { return LevelUpPoint; }
	FORCEINLINE int32 GetGold() const { return Gold; }
	void SetLevel(const int32 InLevel);
	void SetExp(const int32 InExp);
	void SetLevelUpPoint(const int32 InLevelUpPoint);
	void SetGold(const int32 InGold);

	// 권장 - Levelup Event 발생
	void AddLevel(const int32 InLevel);
	void AddExp(const int32 InExp);
	void AddLevelUpPoint(const int32 InLevelUpPoint);
	void AddGold(const int32 InGold);

	//~APlayerState interface
	virtual void Reset() override;
	virtual void ClientInitialize(AController* C) override;
	virtual void CopyProperties(APlayerState* PlayerState) override;
	virtual void OnDeactivated() override;
	virtual void OnReactivated() override;
	//~End of APlayerState interface
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDiaAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDiaAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageNumberWidgetComponent> DamageNumberWidgetCompClass;

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level, Category = "Experience")
	int32 Level = 1;
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Exp, Category = "Experience")
	int32 Exp;
	UFUNCTION()
	void OnRep_Exp(int32 OldExp);

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_LevelUpPoint, Category = "Experience")
	int32 LevelUpPoint;
	UFUNCTION()
	void OnRep_LevelUpPoint(int32 OldLevelUpPoint);

	// 이번 게임에서 얻는 골드량
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Gold, Category = "Experience")
	int32 Gold;
	UFUNCTION()
	void OnRep_Gold(int32 OldGold);

public:
	UFUNCTION(Client, Reliable)
	void OnDamageNumberMessage_Client(AActor* Target, float Damage);
	
	UFUNCTION(Client, Reliable)
	void OnTreasureChestOpen_Client(const TArray<FGameplayTag>& ItemTags);

	/**
	 * 레벨업 시에 얻을 수 있는 VSTag들을 NumSelections 수만큼 뽑음.
	 * 중복을 허용하지 않음.
	 * 
	 * ! const로 인한 BlueprintPure가 강제되어서 Foreach부분에서 강제 다수 실행되었음.
	 * 
	 * @param NumSelections 뽑을 개수 설정
	 * @param bLimitSelectItem true라면 뽑을 패시브와 무기와 현재 가진 값의 합이 6을 넘지 않게 함.  
	 * @return 얻는 태그
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure = false)
	TArray<FGameplayTag> GetRandomVSTagsOnLevelUp(int32 NumSelections = 3) const;

	/**
	 * 전리품 상자에서 얻는 VS Item들을 뽑음.
	 * 1. 현재 있는 아이템 레벨을 업그레이드함. (Max 레벨이 될때까지 중복 허용함)
	 * 2. 업그레이드 할 수 있는 아이템이 없다면 남은 수 만큼 DiaGameplayTags::Pickup_GoldCoin 반환
	 *
	 * ! const로 인한 BlueprintPure가 강제되어서 Foreach부분에서 강제 다수 실행되었음.
	 * 
	 * @param NumSelections 뽑을 개수 
	 * @param RemoveTags Evolution으로 인해 삭제되는 아이템 태그
	 * @return 얻는 태그
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure = false)
	TArray<FGameplayTag> GetRandomVSTagsWhenOpeningTreasureChest(int32 NumSelections, TArray<FGameplayTag>& RemoveTags) const;
};
