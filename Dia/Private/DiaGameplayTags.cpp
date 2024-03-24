#include "DiaGameplayTags.h"

#include "GameplayTagsManager.h"

namespace DiaGameplayTags
{
	// Primary Attribute Tag
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_MaxHealth, "Attribute.Primary.MaxHealth", "Primary MaxHealth");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_HealthRegeneration, "Attribute.Primary.HealthRegeneration", "Primary HealthRegeneration");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Armor, "Attribute.Primary.Armor", "Primary Armor");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_MoveSpeed, "Attribute.Primary.MoveSpeed", "Primary MoveSpeed");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Might, "Attribute.Primary.Might", "Primary Might");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Speed, "Attribute.Primary.Speed", "Primary Speed");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Duration, "Attribute.Primary.Duration", "Primary Duration");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Area, "Attribute.Primary.Area", "Primary Area");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Cooldown, "Attribute.Primary.Cooldown", "Primary Cooldown");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Amount, "Attribute.Primary.Amount", "Primary Amount");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Revival, "Attribute.Primary.Revival", "Primary Revival");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Magnet, "Attribute.Primary.Magnet", "Primary Magnet");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Luck, "Attribute.Primary.Luck", "Primary Luck");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Growth, "Attribute.Primary.Growth", "Primary Growth");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Greed, "Attribute.Primary.Greed", "Primary Greed");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Primary_Curse, "Attribute.Primary.Curse", "Primary Curse");

	// Secondary Attribute Tag
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_MaxHealth, "Attribute.Secondary.MaxHealth", "MaxHealth Attribute.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Secondary_MaxMana, "Attribute.Secondary.MaxMana", "MaxMana Attribute.");

	// Vital Attribute Tag
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Vital_Health, "Attribute.Vital.Health", "Health Attribute.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Vital_Mana, "Attribute.Vital.Mana", "Mana Attribute.");

	// Meta Attribute Tag
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attribute_Meta_InComingExp, "Attribute.Meta.IncomingExp", "Incoming Exp.");

	
	// Input Tag
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_LMB, "InputTag.LMB", "Left Mouse Button");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_RMB, "InputTag.RMB", "Right Mouse Button");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_1, "InputTag.1", "1 Key");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_2, "InputTag.2", "2 Key");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_3, "InputTag.3", "3 Key");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_4, "InputTag.4", "4 Key");

	// Ability
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Attack, "Ability.Attack", "Normal Attack");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS, "Ability.VS", "Vampire Survivors Abilities.");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_Whip, "Ability.VS.Weapon.Whip", "Attacks horizontally, passes through enemies.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_MagicWand, "Ability.VS.Weapon.MagicWand", "Fires at the nearest enemy.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_Knife, "Ability.VS.Weapon.Knife", "Fires at the nearest enemy.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_Axe, "Ability.VS.Weapon.Axe", "High damage, high area scaling");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_Cross, "Ability.VS.Weapon.Cross", "Aims at the nearest enemy, has a boomerang effect.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_KingBible, "Ability.VS.Weapon.KingBible", "Orbits around the character.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_FireWand, "Ability.VS.Weapon.FireWand", "Fires at a random enemy, deals heavy damage.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_Garlic, "Ability.VS.Weapon.Garlic", "Damages nearby enemies. Reduces resistance to knockback and freeze.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_SantaWater, "Ability.VS.Weapon.SantaWater", "Generates damaging zones.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_Runetracer, "Ability.VS.Weapon.Runetracer", "Passes through enemies, bounces around.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_LightningRing, "Ability.VS.Weapon.LightningRing", "Strikes at random enemies.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_Pentagram, "Ability.VS.Weapon.Pentagram", "Erases everything in sight.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_Peachone, "Ability.VS.Weapon.Peachone", "Bombards in a circular area.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_EbonyWings, "Ability.VS.Weapon.EbonyWings", "Bombards in a circular area.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_BloodyTear, "Ability.VS.Weapon.BloodyTear", "Evolution of the whip. Can deal critical damage and absorb HP.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_HolyWand, "Ability.VS.Weapon.HolyWand", "Evolution of the Magic Wand. Fires with no delay.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_ThousandEdge, "Ability.VS.Weapon.ThousandEdge", "Evolved Knife. Fires with no delay.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_DeathSpiral, "Ability.VS.Weapon.DeathSpiral", "Evolved Axe. Passes through enemies.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_HeavenSword, "Ability.VS.Weapon.HeavenSword", "Evolved King Bible. Never Ends.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_UnholyVespers, "Ability.VS.Weapon.UnholyVespers", "Orbits around the character.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_Hellfire, "Ability.VS.Weapon.Hellfire", "Evolved Fire Wand. Passes through enemies.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_SoulEater, "Ability.VS.Weapon.SoulEater", "Evolved Garlic. Steals hearts. Power increases when recovering HP.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_LaBorra, "Ability.VS.Weapon.LaBorra", "Evolved Santa water. Damaging zones follow you and grow when they move.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_NoFuture, "Ability.VS.Weapon.NoFuture", "Evolved Runetracer. Explodes when bouncing and in retaliation.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_ThunderLoop, "Ability.VS.Weapon.ThunderLoop", "Evolved Lightning Ring. Projectiles strike twice.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_GorgeousMoon, "Ability.VS.Weapon.GorgeousMoon", "Evolved Pentagram. Generates extra gems and gathers all of them.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_VS_Weapon_Vandalier, "Ability.VS.Weapon.Vandalier", "Union of Peachone and Ebony Wings.");

	// Effect
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS, "Effect.VS", "Vampire Survivors Effect.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive, "Effect.VS.Passive", "Vampire Survivors Passive Effect.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_Spinach, "Effect.VS.Passive.Spinach", "Raises inflicted damage by 10%.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_Armor, "Effect.VS.Passive.Armor", "Reduces incoming damage by 1. Increases retaliatory damage by 10%.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_HollowHeart, "Effect.VS.Passive.HollowHeart", "Augments max health by 20%.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_Pummarola, "Effect.VS.Passive.Pummarola", "Character recovers 0.2 HP per second.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_EmptyTome, "Effect.VS.Passive.EmptyTome", "Reduces weapons cooldown by 8%.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_Candelabrador, "Effect.VS.Passive.Candelabrador", "Augments area of attacks by 10%.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_Bracer, "Effect.VS.Passive.Bracer", "Increases projectiles speed by 10%.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_Spellbinder, "Effect.VS.Passive.Spellbinder", "Increases duration of weapon effects by 10%.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_Duplicator, "Effect.VS.Passive.Duplicator", "Weapons fire more projectiles.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_Wings, "Effect.VS.Passive.Wings", "Character moves 10% faster.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_Attractorb, "Effect.VS.Passive.Attractorb", "Character pickups items from further away.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_Clover, "Effect.VS.Passive.Clover", "Character gets 10% luckier.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_Crown, "Effect.VS.Passive.Crown", "Character gains 8% more experience.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_StoneMask, "Effect.VS.Passive.StoneMask", "Character earns 10% more coins.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_Tirajisu, "Effect.VS.Passive.Tirajisu", "Character revives with 50% health once.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Passive_SkullOManiac, "Effect.VS.Passive.SkullOManiac", "Increases enemy speed, health, quantity, and frequency by 10%.");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon, "Effect.VS.Weapon", "Vampire Survivors Weapon Effect.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_Whip, "Effect.VS.Weapon.Whip", "Attacks horizontally, passes through enemies.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_MagicWand, "Effect.VS.Weapon.MagicWand", "Fires at the nearest enemy.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_Knife, "Effect.VS.Weapon.Knife", "Fires at the nearest enemy.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_Axe, "Effect.VS.Weapon.Axe", "High damage, high area scaling");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_Cross, "Effect.VS.Weapon.Cross", "Aims at the nearest enemy, has a boomerang effect.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_KingBible, "Effect.VS.Weapon.KingBible", "Orbits around the character.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_FireWand, "Effect.VS.Weapon.FireWand", "Fires at a random enemy, deals heavy damage.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_Garlic, "Effect.VS.Weapon.Garlic", "Damages nearby enemies. Reduces resistance to knockback and freeze.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_SantaWater, "Effect.VS.Weapon.SantaWater", "Generates damaging zones.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_Runetracer, "Effect.VS.Weapon.Runetracer", "Passes through enemies, bounces around.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_LightningRing, "Effect.VS.Weapon.LightningRing", "Strikes at random enemies.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_Pentagram, "Effect.VS.Weapon.Pentagram", "Erases everything in sight.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_Peachone, "Effect.VS.Weapon.Peachone", "Bombards in a circular area.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_EbonyWings, "Effect.VS.Weapon.EbonyWings", "Bombards in a circular area.");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_BloodyTear, "Effect.VS.Weapon.BloodyTear", "Evolution of the whip. Can deal critical damage and absorb HP.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_HolyWand, "Effect.VS.Weapon.HolyWand", "Evolution of the Magic Wand. Fires with no delay.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_ThousandEdge, "Effect.VS.Weapon.ThousandEdge", "Evolved Knife. Fires with no delay.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_DeathSpiral, "Effect.VS.Weapon.DeathSpiral", "Evolved Axe. Passes through enemies.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_HeavenSword, "Effect.VS.Weapon.HeavenSword", "Evolved King Bible. Never Ends.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_UnholyVespers, "Effect.VS.Weapon.UnholyVespers", "Orbits around the character.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_Hellfire, "Effect.VS.Weapon.Hellfire", "Evolved Fire Wand. Passes through enemies.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_SoulEater, "Effect.VS.Weapon.SoulEater", "Evolved Garlic. Steals hearts. Power increases when recovering HP.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_LaBorra, "Effect.VS.Weapon.LaBorra", "Evolved Santa water. Damaging zones follow you and grow when they move.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_NoFuture, "Effect.VS.Weapon.NoFuture", "Evolved Runetracer. Explodes when bouncing and in retaliation.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_ThunderLoop, "Effect.VS.Weapon.ThunderLoop", "Evolved Lightning Ring. Projectiles strike twice.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_GorgeousMoon, "Effect.VS.Weapon.GorgeousMoon", "Evolved Pentagram. Generates extra gems and gathers all of them.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_VS_Weapon_Vandalier, "Effect.VS.Weapon.Vandalier", "Union of Peachone and Ebony Wings.");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Effect_HealthRegeneration, "Effect.HealthRegeneration", "Effect HealthRegeneration.");
	
	// Damage and Heal Type
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Damage_Melee, "Damage.Melee", "Melee Damage");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Damage_Fire, "Damage.Fire", "Fire Damage Type");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Damage_Lightning, "Damage.Lightning", "Lightning Damage Type");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Damage_Arcane, "Damage.Arcane", "Arcane Damage Type");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Damage_Physical, "Damage.Physical", "Physical Damage Type");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Heal, "Heal", "Heal Type");

	// status
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Death, "Status.Death", "Target has the death status.");

	// Event
	DIA_API UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_Montage_Attack, "Event.Montage.Attack", "Attack Event");
	DIA_API UE_DEFINE_GAMEPLAY_TAG_COMMENT(Event_DamageNumber, "Event.DamageNumber", "Damage Number");
	
	// Activation Fail
	DIA_API UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activation_Fail, "Activation.Fail", "Activation Fail");
	
	DIA_API UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activation_Fail_BlockedByTags, "Activation.Fail.BlockedByTags", "Activation Fail: BlockedByTags");
	DIA_API UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activation_Fail_CantAffordCost, "Activation.Fail.CantAffordCost", "Activation Fail: CantAffordCost");
	DIA_API UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activation_Fail_IsDead, "Activation.Fail.IsDead", "Activation Fail: IsDead");
	DIA_API UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activation_Fail_MissingTags, "Activation.Fail.MissingTags", "Activation Fail: MissingTags");
	DIA_API UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activation_Fail_Networking, "Activation.Fail.Networking", "Activation Fail: Networking");
	DIA_API UE_DEFINE_GAMEPLAY_TAG_COMMENT(Activation_Fail_OnCooldown, "Activation.Fail.OnCooldown", "Activation Fail: OnCooldown");

	// Debuff
	DIA_API UE_DEFINE_GAMEPLAY_TAG_COMMENT(Debuff_Garlic, "Debuff.Garlic", "Garlic debuff");

	// Pickup
	DIA_API UE_DEFINE_GAMEPLAY_TAG_COMMENT(Pickup_GoldCoin, "Pickup.GoldCoin", "Gold coin");

}
