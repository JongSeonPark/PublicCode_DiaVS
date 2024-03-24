#include "AbilitySystem/Abilities/Active/DiaBlinkAbility.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"

void UDiaBlinkAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UDiaBlinkAbility::BlinkToLocation(const FVector& GoalLocation)
{
	AActor* Avatar = GetAvatarActorFromActorInfo();

	if (AController* Controller = Avatar->GetInstigatorController())
	{
		Controller->StopMovement();
	}

	// Avatar->SetActorRotation((GoalLocation - Avatar->GetActorLocation()).Rotation().Quaternion());
	const FVector Dir = (GoalLocation - Avatar->GetActorLocation());
	const FRotator Rot(0, FMath::RadiansToDegrees(FMath::Atan2(Dir.Y, Dir.X)), 0);

	Avatar->SetActorRotation(Rot);
	if (const UCapsuleComponent* CapsuleComponent = Avatar->GetComponentByClass<UCapsuleComponent>())
	{
		Avatar->SetActorLocation(GoalLocation + FVector(0, 0, CapsuleComponent->GetScaledCapsuleHalfHeight()));
	}
	else
	{
		Avatar->SetActorLocation(GoalLocation);
	}
}
