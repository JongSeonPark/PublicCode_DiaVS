

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DiaUserWidget.generated.h"

class UDiaWidgetController;

/**
 * 프로젝트에서 사용할 Widget의 부모 클래스입니다.
 * UDiaWidgetController를 부여받아 데이터를 표현 및 컨트롤합니다.(MVC)
 */
UCLASS()
class DIA_API UDiaUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UDiaWidgetController* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDiaWidgetController> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
};
