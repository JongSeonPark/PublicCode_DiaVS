

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageNumberWidgetComponent.generated.h"

USTRUCT()
struct FDamageNumberInfo
{
	GENERATED_BODY()
	
	AActor* Target = nullptr;
	float Damage;
};

/**
 * World에서 Damage를 표현하는 Widget입니다. Blueprint에서 구현합니다.
 */
UCLASS()
class DIA_API UDamageNumberWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage);
};
