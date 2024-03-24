#include "UI/HUD/DiaHUD.h"

#include "UI/Widget/DiaUserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void ADiaHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ADiaHUD::InitOverlay(ADiaPlayerController* PC, ADiaPlayerState* PS, UDiaAbilitySystemComponent* ASC, UDiaAttributeSet* AS)
{
	const FDiaWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* OverlayController = GetWidgetController<UOverlayWidgetController>(WidgetControllerParams);
	if (OverlayWidgetClass)
	{
		UDiaUserWidget* OverlayWidget = CreateWidget<UDiaUserWidget>(GetWorld(), OverlayWidgetClass);
		OverlayWidget->SetWidgetController(OverlayController);
		OverlayController->BroadcastInitValues();
		OverlayWidget->AddToViewport();
	}
}
