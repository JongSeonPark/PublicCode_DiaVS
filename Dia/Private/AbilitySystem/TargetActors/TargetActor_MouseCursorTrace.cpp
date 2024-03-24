#include "AbilitySystem/TargetActors/TargetActor_MouseCursorTrace.h"

#include "NavigationSystem.h"
#include "Character/DiaPlayerCharacter.h"
#include "Components/DecalComponent.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetSystemLibrary.h"

ATargetActor_MouseCursorTrace::ATargetActor_MouseCursorTrace()
{
	// Decal은 Transform Rotation을 조정해야 하기에 Root가 되어서는 안 됨.
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	DecalComponent = CreateDefaultSubobject<UDecalComponent>("Decal");
	RootSceneComponent->SetupAttachment(RootComponent);
	DecalComponent->SetupAttachment(RootSceneComponent);
}

FHitResult ATargetActor_MouseCursorTrace::PerformTrace(AActor* InSourceActor)
{
	if (const ADiaPlayerCharacter* DiaCharacter = Cast<ADiaPlayerCharacter>(InSourceActor))
	{
		if (const APlayerController* PlayerController = DiaCharacter->GetPlayerState()->GetPlayerController())
		{
			FHitResult HitResult;
			PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
			return HitResult;
		}
	}

	return FHitResult();
}
