#pragma once

#include "CoreMinimal.h"
#include "DiaProjectile.h"
#include "DiaExplosionProjectile.generated.h"

class UNiagaraSystem;
class UProjectileMovementComponent;

/**
 * 접촉시 폭팔하여 범위 내 적을 공격하는 투사체입니다. 
 */
UCLASS()
class DIA_API ADiaExplosionProjectile : public ADiaProjectileBase
{
	GENERATED_BODY()

public:
	ADiaExplosionProjectile();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> ExplosionAreaSphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Explosion")
	UNiagaraSystem* FXExplosion;
	void SetArea(const float InArea);

protected:
	UFUNCTION()
	void OnSphereHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSpawnParticleEffect(FVector Location);
	// 클라이언트에서 실행되는 함수
	UFUNCTION(Client, Reliable)
	void SpawnParticleEffectClient(FVector Location);

};
