

#pragma once

#include "CoreMinimal.h"
#include "Actor/Projectile/DiaProjectile.h"
#include "DiaAxe.generated.h"

/**
 * XY축으로 중력이 발생하는 투사체 오브젝트입니다.
 */
UCLASS()
class DIA_API ADiaAxe : public ADiaProjectile
{
	GENERATED_BODY()

public:
	ADiaAxe();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void SetAxeVelocity(const FVector& InVelocity) { AxeVelocity = InVelocity; }

protected:
	// X,Y 값만 사용할 것임.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category=Velocity)
	FVector AxeVelocity;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> LookRoot;
private:
	FVector ComputeAcceleration(float DeltaTime) const;
	FVector ComputeVelocity(const FVector& InVelocity, float DeltaTime) const;
	FVector ComputeMoveDelta(const FVector& InVelocity, float DeltaTime) const;

	UPROPERTY(Replicated)
	FRotator AxeRotatorVelocity;
};
