#include "AbilitySystem/Abilities/Passive/VSLightningRingAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraActor.h"
#include "NiagaraFunctionLibrary.h"
#include "Character/DiaEnemyCharacter.h"
#include "Character/DiaPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UVSLightningRingAbility::OnLoopAbility()
{
	// Repeat하기 전 한번만 계산함.
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (ADiaPlayerCharacter* PlayerCharacter = Cast<ADiaPlayerCharacter>(AvatarActor))
	{
		PlayerCharacter->GetPlayerLookAreaComponent()->GetOverlappingActors(LightningTargets, ADiaEnemyCharacter::StaticClass());
	}

	Super::OnLoopAbility();
}

void UVSLightningRingAbility::RepeatAction(int ActionNumber)
{
	if (LightningTargets.Num() <= 0) return;
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	AActor* TargetActor = LightningTargets[FMath::RandRange(0, LightningTargets.Num() -1)];
	
	FVector LightningLocation = TargetActor->GetActorLocation();

	TArray<FHitResult> OutHits;
	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes { UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };
	TArray<AActor*> ActorsToIgnore{AvatarActor};
	FVector Gap(0, 0, 100);
	
	if (UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), LightningLocation, LightningLocation, GetArea() * 100, ObjectTypes, false, ActorsToIgnore, EDrawDebugTrace::None, OutHits, true))
	{
		UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
		FGameplayEffectContextHandle GameplayEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		GameplayEffectContextHandle.SetAbility(this);
		GameplayEffectContextHandle.AddSourceObject(AvatarActor);
		FGameplayEffectSpecHandle GameplayEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, GetAbilityLevel(), GameplayEffectContextHandle);
		AssignDefaultSetByCallerMagnitude(GameplayEffectSpecHandle);
		for (FHitResult OutHit : OutHits)
		{
			UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OutHit.GetActor());
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data, TargetAbilitySystemComponent);
		}
	}

	// 나이아가라 재생을 위한 액터
	GetWorld()->SpawnActor(SpawnNiagaraActorClass, &LightningLocation);
}