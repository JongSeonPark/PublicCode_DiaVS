


#include "Team/DiaTeamSubsystem.h"

void UDiaTeamSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UDiaTeamSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UDiaTeamSubsystem::CanCauseDamage(const AActor* Instigator, const AActor* Target, bool bAllowDamageToSelf) const
{
	if (bAllowDamageToSelf)
	{
		if (Instigator == Target)
		{
			return true;
		}
	}
	else
	{
		if (Instigator == Target)
		{
			return false;
		}
	}

	// TODO: 추후 Team 시스템으로 바꾸면서 폐기
	return (Instigator->ActorHasTag(FName("Enemy")) && Target->ActorHasTag(FName("Player"))) || 
	(Instigator->ActorHasTag(FName("Player")) && Target->ActorHasTag(FName("Enemy"))); 
}
