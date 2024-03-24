

#pragma once

#include "CoreMinimal.h"
#include "Character/DiaCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "DiaPlayerCharacter.generated.h"

class UBoxComponent;
class UDiaCharacterData;
class UNiagaraSystem;
class UDiaLevelUpInfo;
class USphereComponent;

/**
 * 프로젝트에서 플레이어가 Possess할 캐릭터 클래스입니다.
 */
UCLASS()
class DIA_API ADiaPlayerCharacter : public ADiaCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()

public:
	ADiaPlayerCharacter();

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void ApplyInitialAttributes() const override;
	virtual void InitAbilitySystem() override;

#pragma region Player Interface
	virtual void AddToExp_Implementation(int32 InExp) override;
	virtual int32 GetExp_Implementation() const override;
	virtual void AddToLevel_Implementation(int32 InLevel) override;
	virtual int32 FindLevelForExp_Implementation(int32 InExp, int32& RestExp) const override;
	virtual void SetExp_Implementation(const int32& InExp) override;
	virtual int32 GetExpForCurrentLevel_Implementation() const override;
#pragma endregion

#pragma region Combat Interface
	virtual void Die_Implementation() override;
	virtual int32 GetCharacterLevel_Implementation() const override;
#pragma endregion

	UFUNCTION(Client, Reliable)
	void Die_Client();
	
	UBoxComponent* GetPlayerLookAreaComponent() const { return PlayerLookAreaComponent; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> GemMagnetSphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> PlayerLookAreaComponent;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* ExpPerLevelCurveFloat;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> Niagara_LevelUp;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> LevelUpSound;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Effect")
	TSubclassOf<UGameplayEffect> HealthRegenerationGameplayEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDiaCharacterData* CharacterDefaultReinforceData;
	
private:
	float BaseSpeed;
	float BaseMagnetRadius;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	void AddStartupAbilities();

	UFUNCTION(NetMulticast, Reliable)
	void OnLevelUp();
};
