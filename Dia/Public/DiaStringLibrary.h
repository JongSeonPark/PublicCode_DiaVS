

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DiaStringLibrary.generated.h"

UCLASS()
class DIA_API UDiaStringLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * 분, 초, 센치초를 필요에 따라 포함 및 불포함하도록 구현한 TimeSecondsToString
	 * bIsSeconds만 false일 경우 명백히 이상하게 보일 수 있음.
	 *
	 * DiaGame의 월드타임 표현을 위해 제작되었음.
	 * @return A new string built from the seconds parameter
	 */
	UFUNCTION(BlueprintPure,  Category = "Utilities|String")
	static FString TimeSecondsToString(float InSeconds, bool bIsMinutes, bool bIsSeconds, bool bIsCentiseconds);
};
