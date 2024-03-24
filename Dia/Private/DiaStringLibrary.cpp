#include "DiaStringLibrary.h"

FString UDiaStringLibrary::TimeSecondsToString(float InSeconds, bool bIsMinutes, bool bIsSeconds, bool bIsCentiseconds)
{
	// 음수값 표현
	FString Result = InSeconds < 0.f ? TEXT("-") : TEXT("");
	InSeconds = FMath::Abs(InSeconds);
	bool bRequireColon = false;
	if (bIsMinutes)
	{
		const int32 NumMinutes = FMath::FloorToInt(InSeconds / 60.f);
		InSeconds -= NumMinutes * 60;
		Result += FString::Printf(TEXT("%d"), NumMinutes);
		bRequireColon = true;
	}
	if (bIsSeconds)
	{
		const int32 NumSeconds = FMath::FloorToInt(InSeconds);
		InSeconds -= FMath::FloorToFloat(InSeconds);
		if (bRequireColon) Result += TEXT(":");
		Result += FString::Printf(TEXT("%02d"), NumSeconds);
		bRequireColon = true;
	}
	if (bIsCentiseconds)
	{
		const int32 NumCentiseconds = FMath::FloorToInt(InSeconds);
		if (bRequireColon) Result += TEXT(":");
		Result += FString::Printf(TEXT("%02d"), NumCentiseconds);
	}

	return Result;
}
