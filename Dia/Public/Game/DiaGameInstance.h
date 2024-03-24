#pragma once

#include "CoreMinimal.h"
#include "Data/DiaCharacterData.h"
#include "Data/DiaGameModeData.h"
#include "Data/DiaVSItemDatas.h"
#include "Engine/GameInstance.h"
#include "Save/DiaSaveGame.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "DiaGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FServerData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly)
	FString Name;
	UPROPERTY(BlueprintReadOnly)
	int32 NumOfPlayers = 0;
	UPROPERTY(BlueprintReadOnly)
	int32 MaxPlayers = 0;
	UPROPERTY(BlueprintReadOnly)
	FString HostUserName;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFindSessionsCompleteDynamic);

/**
 * OnlineSubsystem을 활용하기 위해 사용합니다.
 * Save, GameData 등 인게임 내외 필요한 데이터 저장합니다. 
 */
UCLASS()
class DIA_API UDiaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	const TObjectPtr<UDiaSaveGame>& GetSaveData() const { return SaveData; }
	void SetSaveData(const TObjectPtr<UDiaSaveGame>& InSaveData) { this->SaveData = InSaveData; }
	const TMap<FGameplayTag, TObjectPtr<UWeaponStats>>& GetWeaponStatsDatas() const { return WeaponStatsDatas; }
	const TMap<FGameplayTag, TObjectPtr<UPassiveItemStats>>& GetPassiveItemStatsDatas() const { return PassiveItemStatsDatas; }
	const TMap<FGameplayTag, FItemEvolutionInfo>& GetEvoulutionInfos() const { return EvoulutionInfos; }
	const TObjectPtr<UDiaCharacterInfo>& GetCurrentSelectedCharacterInfo() const { return CurrentSelectedCharacterInfo; }
	const TObjectPtr<UDiaStageInfo> GetCurrentSelectedStageInfo() const { return CurrentSelectedStageInfo; }
	UFUNCTION(BlueprintCallable)
	const UItemStatsBase* GetItemStats(const FGameplayTag& GameplayTag) const;
	virtual void Init() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UDiaSaveGame> SaveData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TArray<TObjectPtr<UDiaCharacterInfo>> CharacterInfos;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Character")
	TObjectPtr<UDiaCharacterInfo> CurrentSelectedCharacterInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level")
	TArray<TObjectPtr<UDiaStageInfo>> StageInfos;
	UPROPERTY(BlueprintReadWrite, Category = "Level")
	TObjectPtr<UDiaStageInfo> CurrentSelectedStageInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item", meta = (Categories = "Ability.VS"))
	TMap<FGameplayTag, TObjectPtr<UWeaponStats>> WeaponStatsDatas;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item", meta = (Categories = "Effect.VS"))
	TMap<FGameplayTag, TObjectPtr<UPassiveItemStats>> PassiveItemStatsDatas;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item", meta = (Categories = "Ability.VS"))
	TMap<FGameplayTag, FItemEvolutionInfo> EvoulutionInfos;


#pragma region Online 
public:
	
	// Exec 사용 가는 한 곳: PlayerController, UHD, Cheat Manager, GameMode, Game Instance
	UFUNCTION(Exec, BlueprintCallable)
	void Host(FString ServerName);
	UFUNCTION(Exec, BlueprintCallable)
	void Join(int32 Index);
	UFUNCTION(Exec, BlueprintCallable)
	void FindSession();
	
	// 세션이 시작 되어야 다른 유저가 못 들어온다
	void StartSession();

protected:
	UPROPERTY(BlueprintAssignable)
	FOnFindSessionsCompleteDynamic FindSessionsCompleteDelegate;

	UPROPERTY(BlueprintReadOnly)
	TArray<FServerData> ServerDatas;

	UPROPERTY(BlueprintReadWrite)
	bool bAllowInvasion = false;
	
private:
	FString DesiredServerName;
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	void CreateSession();
	
	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionsComplete(bool Success);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
#pragma endregion Online
};