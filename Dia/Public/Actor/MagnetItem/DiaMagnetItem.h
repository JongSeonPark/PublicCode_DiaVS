

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/CurveTable.h"
#include "DiaMagnetItem.generated.h"

class USphereComponent;

/*
 * ADiaMagnetItem는 캐릭터의 Magnet과 접촉 시, 해당 캐릭터를 따라갑니다.
 * 이후 캐릭터에 접촉 시 아이템 효과 발생(AcceptedActorUpdate)
 */
UCLASS()
class DIA_API ADiaMagnetItem : public AActor
{
	GENERATED_BODY()
public:	
	ADiaMagnetItem();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetItemValue(float Value) {}
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;
	
	// 따라가는 속도에 대한 Properties
	UPROPERTY(EditAnywhere, Category = "Magnet")
	float FollowSpeed = 800.f;
	// 뒤로 약간 빠졌다가 따라가는 속도 커브
	UPROPERTY(EditDefaultsOnly, Category = "Magnet")
	FCurveTableRowHandle FollowSpeedCurve;
	// 따라가고 있는 액터	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> FollowingTarget;

	// 값이 0일때는 LifeSpan을 하지 않음.
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 0.f;
	
	// 액터에게 닿았을 때 효과 적용하는 업데이트. Server에서 진행됨.
	virtual void AcceptedActorUpdate(AActor* CollisionActor) PURE_VIRTUAL(ADiaMagnetItem);
	
private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	float FollowingTime = 0.f;
};
