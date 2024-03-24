#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/DiaPickable.h"
#include "DiaChest.generated.h"

class UWidgetComponent;

/**
 * 클릭을 통해 열리고 아이템을 드랍하는 액터입니다.
 */
UCLASS()
class DIA_API ADiaChest : public AActor, public IDiaPickable
{
	GENERATED_BODY()

public:
	ADiaChest();
	virtual void BeginPlay() override;

	virtual void Pick_Implementation() override;
	virtual void View_Implementation() override;

	UFUNCTION(Reliable, Server)
	void OpenChest();

protected:
	UPROPERTY(EditDefaultsOnly, Category = Chest)
	TObjectPtr<UWidgetComponent> WorldViewWidget;
	
	// TODO: 추후 테이블로 대체
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> SpawnActor;

	UPROPERTY(EditDefaultsOnly)
	int32 SpawnCount = 1;
	
	UPROPERTY(EditDefaultsOnly)
	int32 SpawnRange = 200.f;

private:
};
