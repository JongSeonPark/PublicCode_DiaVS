

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Data/DiaVSItemDatas.h"
#include "GameFramework/Actor.h"
#include "DiaSkillObject.generated.h"

/**
 * 프로젝트에 사용되는 Skill로 인한 오브젝트들의 부모 클래스입니다.
 */
UCLASS()
class DIA_API ADiaSkillObject : public AActor
{
	GENERATED_BODY()
	
public:	
	void SetEffectSpecHandle(const FGameplayEffectSpecHandle& InEffectSpecHandle) { EffectSpecHandle = InEffectSpecHandle; }
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle EffectSpecHandle;

};
