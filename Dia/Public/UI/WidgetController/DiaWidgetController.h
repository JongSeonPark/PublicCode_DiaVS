#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DiaWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedDynamic, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChangedDynamic, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayTagChangedDynamic, FGameplayTag, NewValue);

class ADiaPlayerController;
class ADiaPlayerState;
class UDiaAbilitySystemComponent;
class UDiaAttributeSet;

/**
 * WidgetController로 전달하는 Parameters입니다.
 */
USTRUCT(BlueprintType)
struct FDiaWidgetControllerParams
{
	GENERATED_BODY()
	FDiaWidgetControllerParams() {}
	FDiaWidgetControllerParams(ADiaPlayerController* PC, ADiaPlayerState* PS, UDiaAbilitySystemComponent* ASC, UDiaAttributeSet* AS) : PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<ADiaPlayerController> PlayerController;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<ADiaPlayerState> PlayerState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDiaAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDiaAttributeSet> AttributeSet;
};

/**
 * Widget들과 데이터를 컨트롤 하기 위한 Controller의 부모 클래스입니다.
 */
UCLASS(BlueprintType, Blueprintable)
class DIA_API UDiaWidgetController : public UObject
{
	GENERATED_BODY()

public:
	void SetWidgetControllerParams(const FDiaWidgetControllerParams& WidgetControllerParams);

	// 네트워크 상황일 경우, 특정 오브젝트 지연 로딩으로 인해 초기값이 Bind로 전달이 안 될수도 있음
	// 그래서 초기값을 초기에 호출하는 용도로 사용
	virtual void BroadcastInitValues() {}
	virtual void BindCallbacks() {}

	UPROPERTY(BlueprintReadOnly)
	FDiaWidgetControllerParams WCParams;
};
