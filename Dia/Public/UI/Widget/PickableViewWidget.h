

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickableViewWidget.generated.h"

/**
 * Pickable(바닥에 떨어진 아이템, Chest등) 이름 및 인터렉션 구역을 표현하기 위한 Widget입니다.
 */
UCLASS()
class DIA_API UPickableViewWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TWeakObjectPtr<AActor> PickableItem;
	
	UFUNCTION(BlueprintCallable)
	void TryPick();
};
