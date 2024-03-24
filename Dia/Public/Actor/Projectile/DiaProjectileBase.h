#pragma once

#include "CoreMinimal.h"
#include "Actor/DiaSkillObject.h"
#include "GameFramework/Actor.h"
#include "DiaProjectileBase.generated.h"


class UProjectileMovementComponent;

/**
 * 게임 내의 모든 투사체들의 부모 클래스입니다.
 */
UCLASS()
class DIA_API ADiaProjectileBase : public ADiaSkillObject
{
	GENERATED_BODY()

public:
	ADiaProjectileBase();
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	virtual void SetSpeed(const float InSpeed);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float LifeSpan = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> InitSound;
private:
	TSet<TObjectPtr<AActor>> PierceEnemys;
};
