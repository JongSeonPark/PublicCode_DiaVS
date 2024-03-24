

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Subsystems/EngineSubsystem.h"

/**
 * Singleton for CaptureDefs.
 * 생성 시점: AssetManager StartInitialLoading.. (Init Function)
 */
struct FDiaAttributeCaptureDefs
{
	static FDiaAttributeCaptureDefs& Get() { return Instance; }
	static void Init();
	
private:
	FDiaAttributeCaptureDefs() {}
	void DefineCaptureDefs();
	static FDiaAttributeCaptureDefs Instance;

public:
};
