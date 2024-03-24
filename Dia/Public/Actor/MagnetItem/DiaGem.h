#pragma once

#include "CoreMinimal.h"
#include "DiaMagnetItem.h"
#include "GameFramework/Actor.h"
#include "DiaGem.generated.h"

class UGameplayEffect;
class USphereComponent;

/**
 * 뱀파이어 서바이버즈의 잼(경험치)를 구현합니다.
 */
UCLASS()
class DIA_API ADiaGem : public ADiaMagnetItem
{
	GENERATED_BODY()
public:
	ADiaGem();
	virtual void SetItemValue(float Value) override { ExpBonus = Value; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	UPROPERTY(ReplicatedUsing = OnRep_ExpBonus, EditAnywhere, BlueprintReadWrite, Category = "Gem")
	int32 ExpBonus;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRep_ExpBonus();
	
	virtual void AcceptedActorUpdate(AActor* CollisionActor) override;

	UPROPERTY(EditDefaultsOnly, Category = "Gem")
	TSubclassOf<UGameplayEffect> ExpGameplayEffect;
	
};
