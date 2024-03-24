

#pragma once

#include "CoreMinimal.h"
#include "Actor/SummonedCreature/DiaSummonedCreature.h"
#include "DiaSummonedBird.generated.h"

/**
 * Peachone, Ebony Wings 등을 구현합니다.
 */
UCLASS()
class DIA_API ADiaSummonedBird : public ADiaSummonedCreature
{
	GENERATED_BODY()
public:
	ADiaSummonedBird();
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual void Tick(float DeltaSeconds) override;

	FVector GetFireLocation() const;

private:
	// 움직일 랜덤 레인지
	UPROPERTY(EditDefaultsOnly, Category = "SommonedBird")
	float FloatingRange = 500.f;
	UPROPERTY(EditDefaultsOnly, Category = "SommonedBird")
	float FloatingSpeed = 100.f;

	// 멈춘 뒤 몇초 후에 움직일 것인가
	UPROPERTY(EditDefaultsOnly, Category = "SommonedBird")
	float StopDelay = 1.f;

	FVector MovedLocation;
	FVector RandomPickLocation;
	FVector MoveDirectionVector;

	FTimerHandle RandomLocationTimerHandle;

	void UpdateRandomLocation();
};
