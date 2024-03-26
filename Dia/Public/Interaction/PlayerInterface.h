

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Player 관련 구현 interface
 */
class DIA_API IPlayerInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent)
	void AddToExp(int32 InExp);
	UFUNCTION(BlueprintNativeEvent)
	void AddToLevel(int32 InLevel);
	
	UFUNCTION(BlueprintNativeEvent)
	void SetExp(const int32& InExp);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetExp() const;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 FindLevelForExp(int32 InExp, int32& RestExp) const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetExpForCurrentLevel() const;
};
