


#include "UI/WidgetController/CharacterWidgetController.h"

#include "AbilitySystem/DiaAbilitySystemComponent.h"
#include "AbilitySystem/DiaAttributeSet.h"

void UCharacterWidgetController::BroadcastInitValues()
{
	Super::BroadcastInitValues();
	
	OnMaxHealthChanged.Broadcast(WCParams.AbilitySystemComponent->GetNumericAttribute(UDiaAttributeSet::GetMaxHealthAttribute()));
	OnHealthChanged.Broadcast(WCParams.AbilitySystemComponent->GetNumericAttribute(UDiaAttributeSet::GetHealthAttribute()));
}

void UCharacterWidgetController::BindCallbacks()
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
}
