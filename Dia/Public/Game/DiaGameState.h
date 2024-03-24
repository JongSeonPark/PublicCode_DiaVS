#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DiaGameState.generated.h"

/**
 * 게임 시간을 표현하기 위해 게임 시간(GameStartTimeSeconds)을 따로 Replicated합니다.
 */
UCLASS()
class DIA_API ADiaGameState : public AGameState
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	double GetGameTimeSeconds() const;
	void SetStartTimeSeconds(const double& InGameStartTimeSeconds) { GameStartTimeSeconds = InGameStartTimeSeconds;}
private:
	UPROPERTY(Replicated)
	double GameStartTimeSeconds = UE_DOUBLE_BIG_NUMBER / 2;

};
