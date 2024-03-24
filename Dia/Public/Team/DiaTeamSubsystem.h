#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DiaTeamSubsystem.generated.h"

/**
 * 게임의 Team 관련된 업데이트를 실행합니다.
 * 현재는 적 캐릭터에 대해서만 Tag로 지정.
 */
UCLASS()
class DIA_API UDiaTeamSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	bool CanCauseDamage(const AActor* Instigator, const AActor* Target, bool bAllowDamageToSelf = true) const;
};
