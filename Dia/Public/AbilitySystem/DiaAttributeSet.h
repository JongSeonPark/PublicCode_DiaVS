#pragma once

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "DiaAttributeSet.generated.h"

/**
 * 프로젝트 내 모든 전투 캐릭터가 사용하는 AttributeSet입니다.
 */
UCLASS()
class DIA_API UDiaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UDiaAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma region UAttributeSet interface
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
#pragma endregion End of UAttributeSet

#pragma region Primary Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryDamage, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryDamage;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryDamage);
	UFUNCTION()
	void OnRep_PrimaryDamage(const FGameplayAttributeData& OldDamage) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryMaxHealth, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryMaxHealth;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryMaxHealth);
	UFUNCTION()
	void OnRep_PrimaryMaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryHealthRegeneration, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryHealthRegeneration;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryHealthRegeneration);
	UFUNCTION()
	void OnRep_PrimaryHealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryArmor, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryArmor;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryArmor);
	UFUNCTION()
	void OnRep_PrimaryArmor(const FGameplayAttributeData& OldArmor) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryMoveSpeed, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryMoveSpeed;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryMoveSpeed);
	UFUNCTION()
	void OnRep_PrimaryMoveSpeed(const FGameplayAttributeData& OldMoveSpeed) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryMight, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryMight;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryMight);
	UFUNCTION()
	void OnRep_PrimaryMight(const FGameplayAttributeData& OldMight) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimarySpeed, Category = "Primary Attributes")
	FGameplayAttributeData PrimarySpeed;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimarySpeed);
	UFUNCTION()
	void OnRep_PrimarySpeed(const FGameplayAttributeData& OldSpeed) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryDuration, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryDuration;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryDuration);
	UFUNCTION()
	void OnRep_PrimaryDuration(const FGameplayAttributeData& OldDuration) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryArea, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryArea;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryArea);
	UFUNCTION()
	void OnRep_PrimaryArea(const FGameplayAttributeData& OldArea) const;
	
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryCooldown, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryCooldown;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryCooldown);
	UFUNCTION()
	void OnRep_PrimaryCooldown(const FGameplayAttributeData& OldCooldown) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryAmount, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryAmount;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryAmount);
	UFUNCTION()
	void OnRep_PrimaryAmount(const FGameplayAttributeData& OldAmount) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryRevival, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryRevival;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryRevival);
	UFUNCTION()
	void OnRep_PrimaryRevival(const FGameplayAttributeData& OldRevival) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryMagnet, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryMagnet;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryMagnet);
	UFUNCTION()
	void OnRep_PrimaryMagnet(const FGameplayAttributeData& OldMagnet) const;
	
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryLuck, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryLuck;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryLuck);
	UFUNCTION()
	void OnRep_PrimaryLuck(const FGameplayAttributeData& OldLuck) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryGrowth, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryGrowth;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryGrowth);
	UFUNCTION()
	void OnRep_PrimaryGrowth(const FGameplayAttributeData& OldGrowth) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryGreed, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryGreed;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryGreed);
	UFUNCTION()
	void OnRep_PrimaryGreed(const FGameplayAttributeData& OldGreed) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PrimaryCurse, Category = "Primary Attributes")
	FGameplayAttributeData PrimaryCurse;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, PrimaryCurse);
	UFUNCTION()
	void OnRep_PrimaryCurse(const FGameplayAttributeData& OldCurse) const;
	
#pragma endregion

	// Primary에 의해 값이 변동되는 Attributes
#pragma region Secondary Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, MaxHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
#pragma endregion

#pragma region Vital Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, Health);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

#pragma endregion

	// Replicate 되지 않고 Attribute 값 전달용
#pragma region Meta Attributes
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, IncomingDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingExp;
	ATTRIBUTE_ACCESSORS(UDiaAttributeSet, IncomingExp);

#pragma endregion

protected:
	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;
};
