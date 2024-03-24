
#pragma once

#include "CoreMinimal.h"
#include "AITypes.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "Navigation/PathFollowingComponent.h"
#include "DiaPlayerController.generated.h"

class UDiaCharacterInfo;
class UPathFollowingComponent;
class IDiaPickable;
class UDiaAbilitySystemComponent;
class UDiaInputConfig;
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_MULTICAST_DELEGATE(FOnDiaCharacterDead);

/**
 * 본 프로젝트의 유일한 PlayerController입니다.
 * 키를 통한 Movement 및 ActiveAbility 사용하는 함수를 포함합니다.
 */
UCLASS()
class ADiaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADiaPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	TObjectPtr<UDiaAbilitySystemComponent> DiaAbilitySystemComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = AI)
	TObjectPtr<UPathFollowingComponent> PathFollowingComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input|GAS")
	TObjectPtr<UDiaInputConfig> InputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|GAS", meta=(AllowPrivateAccess = "true"))
	UInputAction* ConfirmTargetAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input|GAS", meta=(AllowPrivateAccess = "true"))
	UInputAction* CancelTargetAction;

	// 키보드를 통한 movement
	void OnMoveTriggerd(const FInputActionValue& InputActionValue);
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);
	
	// 키보드를 통한 Active Abilities 
	void OnAbilityKeyPressed(FGameplayTag InputTag);
	void OnAbilityKeyReleased(FGameplayTag InputTag);
	void OnAbilityKeyHeld(FGameplayTag InputTag);

	// AbilitySystem Target Events
	void OnTargetConfirm();
	void OnTargetCancel();

public:
	FOnDiaCharacterDead OnCharacterDead;
	
	// Client에서 선택한 Character를 Spawn하기 위한 함수
	// GameMode에서 선택된 캐릭터를 스폰하기 위해 실행
	UFUNCTION(Client, Reliable)
	void DiaSpawnCharacter_Client();
	UFUNCTION(Server, Reliable)
	void SpawnCharacter_Server(TSubclassOf<class ADiaPlayerCharacter> CharacterClass);

#pragma region PickupItem
	void TryPickItem(AActor* InPickableItem);
protected:
	UFUNCTION(Reliable, Server)
	void PickItem_Server(AActor* InPickableItem);
	
private:
	TWeakObjectPtr<AActor> PickableItem;
#pragma  endregion

};
