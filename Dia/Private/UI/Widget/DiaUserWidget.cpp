#include "UI/Widget/DiaUserWidget.h"

#include "UI/WidgetController/DiaWidgetController.h"

void UDiaUserWidget::SetWidgetController(UDiaWidgetController* InWidgetController)
{
	WidgetController = InWidgetController;
	OnWidgetControllerSet();
}
