#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/DiaWidgetController.h"
#include "CharacterWidgetController.generated.h"

/**
 * 각각의 캐릭터들의 체력바 위젯 표현을 위한 컨트롤러입니다.
 */
UCLASS()
class DIA_API UCharacterWidgetController : public UDiaWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitValues() override;
	virtual void BindCallbacks() override;

	UPROPERTY(BlueprintAssignable, Category ="GAS|Attribute")
	FOnAttributeChangedDynamic OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category ="GAS|Attribute")
	FOnAttributeChangedDynamic OnMaxHealthChanged;
};
