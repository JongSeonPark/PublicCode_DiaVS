#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/DiaAbilitySystemComponent.h"
#include "AbilitySystem/DiaAttributeSet.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "GameplayEffectTypes.h"
#include "DiaCharacterBase.generated.h"

class UWidgetComponent;
class UCharacterWidgetController;
class UGameplayAbility;

/**
 * 프로젝트에서 사용된 모든 캐릭터들의 클래스입니다.
 * 플레이어와 적들의 캐릭터를 상속합니다.
 * DiaAbilitySystemComponent와 DiaAttribute를 사용하도록 구현되었습니다.
 */
UCLASS(Abstract)
class DIA_API ADiaCharacterBase : public ACharacter, public ICombatInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ADiaCharacterBase();
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UDiaAbilitySystemComponent* GetDiaAbilitySystemComponent() const { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	UDiaAttributeSet* GetDiaAttributeSet() const { return AttributeSet; }

#pragma region Combat Interface
	virtual void Die_Implementation() override;
	virtual bool IsDead_Implementation() override { return bDead; }
#pragma endregion

	FORCEINLINE bool IsDead() const { return bDead; }
	UFUNCTION(NetMulticast, Reliable)
	void Die_Multicast();
	
protected:
	void UpdateHpBarWidgetController();
	virtual void InitAbilitySystem();
	virtual void ApplyInitialAttributes() const;
	void ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level = 1.f) const;

	UFUNCTION(BlueprintCallable)
	void DoRagdoll() const;
	void CancelAbilitiesWhenCharacterDie();

	UPROPERTY()
	TObjectPtr<UDiaAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UDiaAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attirubutes")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attirubutes")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attirubutes")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;

	bool bDead = false;

	UPROPERTY()
	TObjectPtr<UCharacterWidgetController> CharacterWidgetController;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> HpBarWidget;

	virtual void OnImcomingDamage(const FOnAttributeChangeData& Data);

	void PushOtherCharacter(ACharacter* OtherCharacter);

	UFUNCTION()
	void OnHitOtherCharacter(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
