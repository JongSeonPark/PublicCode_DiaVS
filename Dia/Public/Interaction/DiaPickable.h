

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DiaPickable.generated.h"

UINTERFACE(BlueprintType, MinimalAPI)
class UDiaPickable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 플레이어가 Map 내에서 마우스를 통해 잡을 수 있는 오브젝트(상자, 아이템 등)를 위한 Interface
 */
class DIA_API IDiaPickable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Pick)
	void Pick();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Pick)
	void View();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Pick)
	bool IsAutoView();
	
	UFUNCTION(Category = Pick)
	virtual bool IsActive() { return false; };
};
