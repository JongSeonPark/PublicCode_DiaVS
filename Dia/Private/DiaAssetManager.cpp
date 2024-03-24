

#include "DiaAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "DiaAttributeCaptureDefs.h"
#include "DiaGameplayTags.h"


void UDiaAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UE_LOG(LogTemp, Warning, TEXT("UDiaAssetManager StartInitialLoading"));

	// Init Singletons..
	FDiaAttributeCaptureDefs::Init();
	
	/*
	 *  4.24부터는 UAbilitySystemGlobals::Get().InitGlobalData()를 호출하여 TargetData를 사용합니다.
	 * 샘플 프로젝트는 이 작업을UAssetManager::StartInitialLoading()을 수행합니다.
	 * 자세한 내용은 InitGlobalData()를 참조하세요.
	 */
	UAbilitySystemGlobals::Get().InitGlobalData();
}
