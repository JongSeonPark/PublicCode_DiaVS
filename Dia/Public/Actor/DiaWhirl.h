

#pragma once

#include "CoreMinimal.h"
#include "DiaSkillObject.h"
#include "GameFramework/Actor.h"
#include "DiaWhirl.generated.h"

class UGameplayEffect;

/**
 * 주위를 빙글빙글 도는 스킬 오브젝트입니다.
 * KingBible에서 사용되었습니다.
 */
UCLASS()
class DIA_API ADiaWhirl : public ADiaSkillObject
{
	GENERATED_BODY()
public:	
	ADiaWhirl();
	
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class URotatingMovementComponent> RotatingMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Whirl")
	int32 ObjectCount = 1;

	UPROPERTY(EditAnywhere, Category = "Whirl")
	float Range = 100.f;
	
	UPROPERTY()
	TArray<TObjectPtr<class USphereComponent>> CollisionObjects;
	
	UPROPERTY(EditAnywhere, Category = "Whirl")
	TSubclassOf<UPrimitiveComponent> LookComponentClass;
	
	UPROPERTY(EditAnywhere, Category = "Whirl")
	TSubclassOf<AActor> LookActorClass;

	TArray<AActor*> LookActors;
};
