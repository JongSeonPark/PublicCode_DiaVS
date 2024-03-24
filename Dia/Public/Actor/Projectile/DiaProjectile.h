

#pragma once

#include "CoreMinimal.h"
#include "DiaProjectileBase.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "DiaProjectile.generated.h"

class UProjectileMovementComponent;

/**
 * 접촉을 통해 적에게 공격하는 투사체들의 부모 클래스입니다.
 */
UCLASS()
class DIA_API ADiaProjectile : public ADiaProjectileBase
{
	GENERATED_BODY()
	
public:	
	ADiaProjectile();
	void SetPierce(const int32 InPierce) { Pierce = InPierce; }
	
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// 0이면 무한
	UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (ClampMin = 0))
	int32 Pierce = 1;

private:
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	TSet<TObjectPtr<AActor>> PierceEnemys;
};
