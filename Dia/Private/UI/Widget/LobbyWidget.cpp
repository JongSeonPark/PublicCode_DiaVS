#include "UI/Widget/LobbyWidget.h"

#include "Game/DiaGameInstance.h"

void ULobbyWidget::TestTravel1()
{
	if (const UDiaGameInstance* DiaGameInstance = GetGameInstance<UDiaGameInstance>())
	{
		TObjectPtr<UDiaStageInfo> DiaStageInfo = DiaGameInstance->GetCurrentSelectedStageInfo();

		if (DiaStageInfo && !DiaStageInfo->Level.GetLongPackageName().IsEmpty())
		{
			FString URL = DiaStageInfo->Level.GetLongPackageName();
			UWorld* World = GetWorld();

			APlayerController* PlayerController = World->GetFirstPlayerController(); 
			PlayerController->ClientTravel(DiaStageInfo->Level.GetLongPackageName(), TRAVEL_Absolute);

			FInputModeGameOnly InputModeData;
			SetIsFocusable(false);
			PlayerController->SetInputMode(InputModeData);
		}
	}
}
