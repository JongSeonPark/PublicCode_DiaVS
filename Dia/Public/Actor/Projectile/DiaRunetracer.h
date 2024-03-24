

#pragma once

#include "CoreMinimal.h"
#include "Actor/Projectile/DiaProjectile.h"
#include "DiaRunetracer.generated.h"

class UBoxComponent;
/**
 * 화면 가장자리를 튕기며 돌아다니는 투사체입니다.
 */
UCLASS()
class DIA_API ADiaRunetracer : public ADiaProjectile
{
	GENERATED_BODY()
public:
	ADiaRunetracer();
	TWeakPtr<UBoxComponent> BoxAreaComponent;

	virtual void Tick(float DeltaSeconds) override;
};
