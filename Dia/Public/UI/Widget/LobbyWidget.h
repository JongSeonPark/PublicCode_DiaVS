

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UDiaGameInstance;

/**
 * 로비의 Widget입니다.
 */
UCLASS()
class DIA_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void TestTravel1();

};
