

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/DiaWidgetController.h"
#include "DiaHUD.generated.h"

class UDiaUserWidget;
struct FDiaWidgetControllerParams;
class UDiaWidgetController;

UCLASS()
class DIA_API ADiaHUD : public AHUD
{
	GENERATED_BODY()
public:

	/**
	 * 
	 * @tparam T UDiaWidgetController의 자식 클래스
	 * @return T Type
	 */
	template<typename T>
	T* GetWidgetController(const FDiaWidgetControllerParams& WCParams);
	virtual void BeginPlay() override;

	void InitOverlay(ADiaPlayerController* PC, ADiaPlayerState* PS, UDiaAbilitySystemComponent* ASC, UDiaAttributeSet* AS);

private:

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UDiaWidgetController>> DiaWidgetControllerClasses;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDiaUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TMap<TSubclassOf<UDiaWidgetController>, TObjectPtr<UDiaWidgetController>> DiaWidgetControllerClassToObject; 
};

template <typename T>
T* ADiaHUD::GetWidgetController(const FDiaWidgetControllerParams& WCParams)
{
	for (const auto Pair : DiaWidgetControllerClassToObject)
	{
		const TSubclassOf<UDiaWidgetController> WCClass = Pair.Key;
		TObjectPtr<UDiaWidgetController> WC = Pair.Value;
		
		if (WCClass->IsChildOf(T::StaticClass()))
		{
			return Cast<T>(WC.Get());
		}
	}
	
	for (TSubclassOf<UDiaWidgetController> WCClass : DiaWidgetControllerClasses)
	{
		if (WCClass->IsChildOf(T::StaticClass()))
		{
			T* WC = NewObject<T>(this, WCClass);
			WC->SetWidgetControllerParams(WCParams);
			WC->BindCallbacks();
			DiaWidgetControllerClassToObject.Add(WCClass, WC);
			return WC;
		}
	}

	return nullptr;
}
