


#include "UI/Widget/PickableViewWidget.h"

#include "Player/DiaPlayerController.h"

void UPickableViewWidget::TryPick()
{
	if (ADiaPlayerController* PlayerController = Cast<ADiaPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PlayerController->TryPickItem(PickableItem.Get());
	}
}
