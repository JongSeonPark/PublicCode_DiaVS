#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/DiaAttributeSet.h"
#include "AbilitySystem/DiaAbilitySystemComponent.h"
#include "DiaGameplayTags.h"
#include "Interaction/PlayerInterface.h"
#include "Player/DiaPlayerController.h"
#include "Player/DiaPlayerState.h"

void UOverlayWidgetController::BroadcastInitValues()
{
	Super::BroadcastInitValues();
	OnMaxHealthChanged.Broadcast(WCParams.AttributeSet->GetMaxHealth());
	OnHealthChanged.Broadcast(WCParams.AttributeSet->GetHealth());
	OnExpChanged.Broadcast(WCParams.PlayerState->GetExp());
	OnLevelChanged.Broadcast(WCParams.PlayerState->GetPlayerLevel());
	OnLevelUpPointChanged.Broadcast(WCParams.PlayerState->GetLevelUpPoint());
	OnGoldChanged.Broadcast(WCParams.PlayerState->GetGold());

	// VS Effect Added.
	TArray<FGameplayEffectSpec> EffectSpecs;
	WCParams.AbilitySystemComponent->GetAllActiveGameplayEffectSpecs(EffectSpecs);
	for (FGameplayEffectSpec EffectSpec : EffectSpecs)
	{
		OnActiveGameplayEffectAddedToSelf(WCParams.AbilitySystemComponent, EffectSpec, FActiveGameplayEffectHandle());
	}
}

void UOverlayWidgetController::BindCallbacks()
{
	Super::BindCallbacks();

	WCParams.AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WCParams.AttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});
	WCParams.AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WCParams.AttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});

	WCParams.PlayerState->OnExpChanged.AddLambda(
		[this](int32 NewValue)
		{
			OnExpChanged.Broadcast(NewValue);
		});
	WCParams.PlayerState->OnLevelChanged.AddLambda(
		[this](int32 NewValue)
		{
			OnLevelChanged.Broadcast(NewValue);
		});
	WCParams.PlayerState->OnLevelUpPointChanged.AddLambda(
		[this](int32 NewValue)
		{
			OnLevelUpPointChanged.Broadcast(NewValue);
		});
	WCParams.PlayerState->OnGoldChanged.AddLambda(
		[this](int32 NewValue)
		{
			OnGoldChanged.Broadcast(NewValue);
		});

	WCParams.AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &ThisClass::OnActiveGameplayEffectAddedToSelf);
	WCParams.AbilitySystemComponent->OnAnyGameplayEffectRemovedDelegate().AddUObject(this, &ThisClass::OnAnyGameplayEffectRemoved);

	WCParams.PlayerState->OnTreasureChestOpened.AddLambda([this](TArray<FGameplayTag> ItemTags)
	{
		OnTreasureChestOpened.Broadcast(ItemTags);
	});
	
	WCParams.PlayerController->OnCharacterDead.AddLambda([this]()
	{
		OnCharacterDead.Broadcast();
	});
}

int32 UOverlayWidgetController::GetExpForCurrentLevel() const
{
	return WCParams.AbilitySystemComponent->GetAvatarActor()->Implements<UPlayerInterface>() ? IPlayerInterface::Execute_GetExpForCurrentLevel(WCParams.AbilitySystemComponent->GetAvatarActor()) : 0;
}

void UOverlayWidgetController::OnAnyGameplayEffectRemoved(const FActiveGameplayEffect& Effect)
{
	FGameplayTagContainer AssetTags;
	FGameplayTagContainer FilterTags;
	FilterTags.AddTag(DiaGameplayTags::Ability_VS);
	FilterTags.AddTag(DiaGameplayTags::Effect_VS);
	Effect.Spec.GetAllAssetTags(AssetTags);
	FGameplayTagContainer VSTagContainer = AssetTags.Filter(FilterTags);
	for (const FGameplayTag Tag : VSTagContainer)
	{
		OnVSEffectRemoved.Broadcast(Tag);
	}
}

void UOverlayWidgetController::OnActiveGameplayEffectAddedToSelf(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer AssetTags;
	FGameplayTagContainer FilterTags;
	FilterTags.AddTag(DiaGameplayTags::Ability_VS);
	FilterTags.AddTag(DiaGameplayTags::Effect_VS);
	EffectSpec.GetAllAssetTags(AssetTags);
	FGameplayTagContainer VSPassiveTagContainer = AssetTags.Filter(FilterTags);
	for (const FGameplayTag Tag : VSPassiveTagContainer)
	{
		OnVSEffectAdded.Broadcast(Tag);
	}
}
