#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "Subsystems/EngineSubsystem.h"

/**
 * Extern style로 Native GameplayTag를 생성합니다.
 * GameplayTag 네이밍 규칙은 특별한 경우가 아니라면 계층에서도 단수를 유지하겠습니다. 
 */
namespace DiaGameplayTags
{
#pragma region Attribute
	// Primary
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_MaxHealth);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_HealthRegeneration);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Armor);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_MoveSpeed);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Might);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Speed);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Duration);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Area);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Cooldown);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Amount);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Revival);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Magnet);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Luck);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Growth);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Greed);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Primary_Curse);

	// Secondary
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MaxHealth);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Secondary_MaxMana);

	// Vital
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Health);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Vital_Mana);

	// Meta Exp, Level 등
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Meta_InComingExp);

#pragma endregion

#pragma region Input
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LMB);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_RMB);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_1);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_2);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_3);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_4);

#pragma endregion

#pragma region Ability
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Attack);
	
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_Whip);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_MagicWand);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_Knife);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_Axe);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_Cross);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_KingBible);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_FireWand);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_Garlic);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_SantaWater);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_Runetracer);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_LightningRing);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_Pentagram);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_Peachone);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_EbonyWings);
	
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_BloodyTear);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_HolyWand);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_ThousandEdge);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_DeathSpiral);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_HeavenSword);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_UnholyVespers);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_Hellfire);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_SoulEater);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_LaBorra);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_NoFuture);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_ThunderLoop);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_GorgeousMoon);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_VS_Weapon_Vandalier);
	
#pragma endregion

#pragma region Effect
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_Spinach);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_Armor);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_HollowHeart);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_Pummarola);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_EmptyTome);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_Candelabrador);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_Bracer);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_Spellbinder);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_Duplicator);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_Wings);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_Attractorb);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_Clover);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_Crown);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_StoneMask);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_Tirajisu);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Passive_SkullOManiac);
	
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_Whip);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_MagicWand);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_Knife);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_Axe);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_Cross);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_KingBible);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_FireWand);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_Garlic);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_SantaWater);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_Runetracer);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_LightningRing);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_Pentagram);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_Peachone);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_EbonyWings);
	
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_BloodyTear);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_HolyWand);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_ThousandEdge);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_DeathSpiral);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_HeavenSword);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_UnholyVespers);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_Hellfire);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_SoulEater);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_LaBorra);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_NoFuture);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_ThunderLoop);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_GorgeousMoon);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_VS_Weapon_Vandalier);

	
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_HealthRegeneration);

#pragma endregion

#pragma region Damage And Heal Type
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Melee);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Fire);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Lightning);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Arcane);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Physical);
	
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Heal);

#pragma endregion

#pragma region Status
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death);

#pragma endregion
	
#pragma region Event
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Montage_Attack);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_DamageNumber);

#pragma endregion
	
#pragma region Activation Fail
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Activation_Fail);
	
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Activation_Fail_BlockedByTags);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Activation_Fail_CantAffordCost);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Activation_Fail_IsDead);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Activation_Fail_MissingTags);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Activation_Fail_Networking);
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Activation_Fail_OnCooldown);

#pragma endregion

#pragma region Debuff
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Debuff_Garlic);
#pragma endregion

#pragma region Pickup
	DIA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pickup_GoldCoin);
#pragma endregion
	
}
