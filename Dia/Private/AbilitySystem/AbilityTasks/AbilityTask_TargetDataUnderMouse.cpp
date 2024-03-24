#include "AbilitySystem/AbilityTasks/AbilityTask_TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UAbilityTask_TargetDataUnderMouse* UAbilityTask_TargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	return NewAbilityTask<UAbilityTask_TargetDataUnderMouse>(OwningAbility);
}

void UAbilityTask_TargetDataUnderMouse::Activate()
{
	Super::Activate();
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());

		const TWeakObjectPtr<APlayerController> PlayerController = Ability->GetCurrentActorInfo()->PlayerController;
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
		TargetData->HitResult = HitResult;

		FGameplayAbilityTargetDataHandle DataHandle;
		DataHandle.Add(TargetData);

		// Sever RPC
		AbilitySystemComponent->ServerSetReplicatedTargetData(
			GetAbilitySpecHandle(),
			GetActivationPredictionKey(),
			DataHandle,
			FGameplayTag(),
			AbilitySystemComponent->ScopedPredictionKey
		);

		if (ShouldBroadcastAbilityTaskDelegates())
		{
			ValidData.Broadcast(DataHandle);
		}
	}
	else
	{
		AbilitySystemComponent->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey()).AddLambda(
			[this](const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
			{
				AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
				if (ShouldBroadcastAbilityTaskDelegates())
				{
					ValidData.Broadcast(DataHandle);
				}
			});
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(), GetActivationPredictionKey());
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}
