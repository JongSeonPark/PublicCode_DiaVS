#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "UObject/NoExportTypes.h"
#include "DiaGameplayEffectContext.generated.h"

/**
 * 추가 정보를 통신하기 위해 새로 만든 FGameplayEffectContext입니다.
 * UDiaAbilitySystemGlobals에서 사용되었습니다.
 */
USTRUCT()
struct DIA_API FDiaGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	static FDiaGameplayEffectContext* ExtractEffectContext(struct FGameplayEffectContextHandle Handle);

	/** !! 반드시 구현 GetScriptStruct, Duplicate */
	virtual UScriptStruct* GetScriptStruct() const override { return FDiaGameplayEffectContext::StaticStruct(); }
	virtual FDiaGameplayEffectContext* Duplicate() const
	{
		FDiaGameplayEffectContext* NewContext = new FDiaGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;

	int32 TestInt = 3;
};

template <>
struct TStructOpsTypeTraits<FDiaGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FDiaGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};
