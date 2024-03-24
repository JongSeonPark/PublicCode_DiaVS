
#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DiaAssetManager.generated.h"

UCLASS()
class DIA_API UDiaAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
protected:
	virtual void StartInitialLoading() override;
};
