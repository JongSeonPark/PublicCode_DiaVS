

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/DiaPickable.h"
#include "DiaDroppedItem.generated.h"

class UWidgetComponent;
class UNiagaraComponent;
class UActorSequenceComponent;

/**
 * 바닥에 떨어진 아이템을 구현합니다.
 * 본 프로젝트에서 사용되지 않았습니다.
 */
UCLASS()
class DIA_API ADiaDroppedItem : public AActor, public IDiaPickable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADiaDroppedItem();

	virtual void Pick_Implementation() override;
	virtual void View_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = DroppedItem)
	TObjectPtr<UNiagaraComponent> ItemHighlightNiagara;
	UPROPERTY(EditDefaultsOnly, Category = DroppedItem)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly, Category = DroppedItem)
	TObjectPtr<UWidgetComponent> WorldViewWidget;

private:
	UFUNCTION(BlueprintCallable)
	void OnFinish_SequencePlay();
};
