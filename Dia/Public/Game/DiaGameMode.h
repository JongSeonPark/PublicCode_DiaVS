#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "UI/Widget/DamageNumberWidgetComponent.h"
#include "DiaGameMode.generated.h"

class UDiaGameModeData;
class UDiaGameSpawner;
class ADiaEnemyCharacter;

/**
 * 각각의 스테이지에서 사용할 게임모드입니다.
 */
UCLASS()
class DIA_API ADiaGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ADiaGameMode();
	//~AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

	//~AGameModeBase interface
	virtual void OnPostLogin(AController* NewPlayer) override;
	virtual void PreInitializeComponents() override;
	virtual void StartPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDiaGameModeData> DiaGameModeData;
	UDiaGameSpawner* GetDiaGameSpawner() const {return DiaGameSpawner;}
	
private:
	UPROPERTY()
	TObjectPtr<UDiaGameSpawner> DiaGameSpawner;
	TArray<FGameplayMessageListenerHandle> ListenerHandles;
	void OnDamageNumberMessage(FGameplayTag Channel, const FDamageNumberInfo& Payload);

};
