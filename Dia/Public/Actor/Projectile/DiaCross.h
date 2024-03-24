#pragma once

#include "CoreMinimal.h"
#include "Actor/Projectile/DiaProjectile.h"
#include "DiaCross.generated.h"

/**
 * 앞으로 발사한 뒤, 반대방향으로 가속하는 투사체입니다.
 */
UCLASS()
class DIA_API ADiaCross : public ADiaProjectile
{
	GENERATED_BODY()

public:
	ADiaCross();
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, Category = "Cross")
	float BackwardSpeed = 1000.f;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> LookRoot;
	FRotator CrossRotatorVelocity = FRotator(0, 720, 0);
};
