

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/DiaWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTreasureChestOpenedDynamic, const TArray<FGameplayTag>&, RewardTags);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDiaCharacterDeadDynamic);

/**
 * Overlay Widget(인게임 상 UI)를 제어하기 위한 컨트롤러입니다.
 */
UCLASS()
class DIA_API UOverlayWidgetController : public UDiaWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitValues() override;
	virtual void BindCallbacks() override;

	UPROPERTY(BlueprintAssignable, Category ="GAS|Attribute")
	FOnAttributeChangedDynamic OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category ="GAS|Attribute")
	FOnAttributeChangedDynamic OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category ="GAS|Stat")
	FOnPlayerStatChangedDynamic OnExpChanged;
	UPROPERTY(BlueprintAssignable, Category ="GAS|Stat")
	FOnPlayerStatChangedDynamic OnLevelChanged;
	UPROPERTY(BlueprintAssignable, Category ="GAS|Stat")
	FOnPlayerStatChangedDynamic OnLevelUpPointChanged;
	UPROPERTY(BlueprintAssignable, Category ="GAS|Stat")
	FOnPlayerStatChangedDynamic OnGoldChanged;
	UPROPERTY(BlueprintAssignable, Category ="GAS|Stat")
	FOnGameplayTagChangedDynamic OnVSEffectAdded;
	UPROPERTY(BlueprintAssignable, Category ="GAS|Stat")
	FOnGameplayTagChangedDynamic OnVSEffectRemoved;
	UPROPERTY(BlueprintAssignable, Category ="GAS|Stat")
	FOnDiaCharacterDeadDynamic OnCharacterDead;

	UPROPERTY(BlueprintAssignable, Category ="GAS")
	FOnTreasureChestOpenedDynamic OnTreasureChestOpened;

	UFUNCTION(BlueprintCallable)
	int32 GetExpForCurrentLevel() const;

	UFUNCTION()
	void OnAnyGameplayEffectRemoved(const FActiveGameplayEffect& Effect);
	UFUNCTION()
	void OnActiveGameplayEffectAddedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
