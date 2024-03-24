#include "Game/DiaGameState.h"

#include "GameplayTagContainer.h"
#include "AbilitySystem/DiaGameplayEffectContext.h"
#include "Dia/Dia.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

void ADiaGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADiaGameState, GameStartTimeSeconds);
}

double ADiaGameState::GetGameTimeSeconds() const
{
	return FMath::Max(0, GetServerWorldTimeSeconds() - GameStartTimeSeconds);
}