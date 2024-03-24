#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DiaSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DIA_API UDiaSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UDiaSaveGame();
	virtual void FinishDestroy() override;

protected:
	UPROPERTY(BlueprintReadWrite)
	FString SlotName;
	UPROPERTY(EditAnywhere)
	uint32 UserIndex;

};
