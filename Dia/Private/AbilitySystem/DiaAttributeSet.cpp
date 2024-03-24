#include "AbilitySystem/DiaAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "DiaGameplayTags.h"
#include "Net/UnrealNetwork.h"

#include "GameplayEffectExtension.h"
#include "AbilitySystem/DiaGameplayEffectContext.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/PlayerInterface.h"
#include "UI/Widget/DamageNumberWidgetComponent.h"

UDiaAttributeSet::UDiaAttributeSet()
{
}

void UDiaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Primary
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryMaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryHealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryMoveSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryMight, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimarySpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryDuration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryArea, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryCooldown, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryAmount, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryRevival, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryMagnet, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryLuck, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryGrowth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryGreed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, PrimaryCurse, COND_None, REPNOTIFY_Always);

	// Secondary
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	// Vital
	DOREPLIFETIME_CONDITION_NOTIFY(UDiaAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

void UDiaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	ClampAttribute(Attribute, NewValue);
}

void UDiaAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	// PrimaryMaxHealth값 변경이 있었을 때(아이템으로 인한 최대 체력 변화), 증가 값이면 현재 체력 또한 증가
	if (Attribute == GetPrimaryMaxHealthAttribute() && NewValue > OldValue)
	{
		SetHealth(GetHealth() + (NewValue - OldValue));
	}
}

void UDiaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// 대미지 적용 및 죽음
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		float IncommingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		const float NewHealth = GetHealth() - IncommingDamage;
		SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

		if (IncommingDamage > 0.f)
		{
			const FDiaGameplayEffectContext* DiaEffectContext = static_cast<const FDiaGameplayEffectContext*>(Data.EffectSpec.GetEffectContext().Get());
			
			UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
			const FDamageNumberInfo DamageNumberInfo(Data.Target.GetAvatarActor(), IncommingDamage);
			MessageSubsystem.BroadcastMessage(DiaGameplayTags::Event_DamageNumber, DamageNumberInfo);
		}

		const bool bFatal = GetHealth() <= 0;
		if (bFatal)
		{
			// Player 기준 OwningActor는 Playerstate AvatarActor가 DiaCharacter
			AActor* AvatarActor = Data.Target.GetAvatarActor();
			if (AvatarActor->Implements<UCombatInterface>())
			{
				if (!ICombatInterface::Execute_IsDead(AvatarActor))
					ICombatInterface::Execute_Die(AvatarActor);
			}
		}
	}

	// 경험치 및 레벨업
	if (Data.EvaluatedData.Attribute == GetIncomingExpAttribute())
	{
		// Primary Growth Update
		const float LocalIncomingExp = GetIncomingExp() * (1.f + GetPrimaryGrowth());
		SetIncomingExp(0.f);
		AActor* AvatarActor = Data.Target.GetAvatarActor();
		
		if (AvatarActor->Implements<UPlayerInterface>() && AvatarActor->Implements<UCombatInterface>())
		{
			const int32 CurrentLevel = ICombatInterface::Execute_GetCharacterLevel(AvatarActor);
			const int32 CurrentExp = IPlayerInterface::Execute_GetExp(AvatarActor);

			int32 RestExp;
			const int32 NewLevel = IPlayerInterface::Execute_FindLevelForExp(AvatarActor, CurrentExp + LocalIncomingExp, RestExp);
			const int32 PlusLevel = NewLevel - CurrentLevel;
			if (PlusLevel > 0)
			{
				IPlayerInterface::Execute_AddToLevel(AvatarActor, PlusLevel);
				IPlayerInterface::Execute_SetExp(AvatarActor, RestExp);
			}
			else
			{
				IPlayerInterface::Execute_AddToExp(AvatarActor, LocalIncomingExp);
			}
		}
	}

}

#pragma region OnRep

void UDiaAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, MaxHealth, OldMaxHealth);
}

void UDiaAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, Health, OldHealth);
}

void UDiaAttributeSet::OnRep_PrimaryDamage(const FGameplayAttributeData& OldDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryDamage, OldDamage);
}

void UDiaAttributeSet::OnRep_PrimaryMaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryMaxHealth, OldMaxHealth);
}

void UDiaAttributeSet::OnRep_PrimaryHealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryHealthRegeneration, OldHealthRegeneration);
}

void UDiaAttributeSet::OnRep_PrimaryArmor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryArmor, OldArmor);
}

void UDiaAttributeSet::OnRep_PrimaryMoveSpeed(const FGameplayAttributeData& OldMoveSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryMoveSpeed, OldMoveSpeed);
}

void UDiaAttributeSet::OnRep_PrimaryMight(const FGameplayAttributeData& OldMight) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryMight, OldMight);
}

void UDiaAttributeSet::OnRep_PrimarySpeed(const FGameplayAttributeData& OldSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimarySpeed, OldSpeed);
}

void UDiaAttributeSet::OnRep_PrimaryDuration(const FGameplayAttributeData& OldDuration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryDuration, OldDuration);
}

void UDiaAttributeSet::OnRep_PrimaryArea(const FGameplayAttributeData& OldArea) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryArea, OldArea);
}

void UDiaAttributeSet::OnRep_PrimaryCooldown(const FGameplayAttributeData& OldCooldown) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryCooldown, OldCooldown);
}

void UDiaAttributeSet::OnRep_PrimaryAmount(const FGameplayAttributeData& OldAmount) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryAmount, OldAmount);
}

void UDiaAttributeSet::OnRep_PrimaryRevival(const FGameplayAttributeData& OldRevival) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryRevival, OldRevival);
}

void UDiaAttributeSet::OnRep_PrimaryMagnet(const FGameplayAttributeData& OldMagnet) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryMagnet, OldMagnet);
}

void UDiaAttributeSet::OnRep_PrimaryLuck(const FGameplayAttributeData& OldLuck) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryLuck, OldLuck);
}

void UDiaAttributeSet::OnRep_PrimaryGrowth(const FGameplayAttributeData& OldGrowth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryGrowth, OldGrowth);
}

void UDiaAttributeSet::OnRep_PrimaryGreed(const FGameplayAttributeData& OldGreed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryGreed, OldGreed);
}

void UDiaAttributeSet::OnRep_PrimaryCurse(const FGameplayAttributeData& OldCurse) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaAttributeSet, PrimaryCurse, OldCurse);
}
#pragma endregion

void UDiaAttributeSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	// 아래 Attribute들의 경우 보통 BaseValue와 CurrentValue의 구별이 없을 것이므로 두개의 변동 모두 호출해야 함.
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}
