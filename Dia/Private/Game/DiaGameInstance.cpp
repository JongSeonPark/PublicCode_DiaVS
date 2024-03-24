#include "Game/DiaGameInstance.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Dia/Dia.h"
#include "Net/UnrealNetwork.h"
#include "Online/OnlineSessionNames.h"

const static FName SESSION_NAME = TEXT("Game");
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("ServerName");

const UItemStatsBase* UDiaGameInstance::GetItemStats(const FGameplayTag& GameplayTag) const
{
	if (WeaponStatsDatas.Contains(GameplayTag))
	{
		return WeaponStatsDatas[GameplayTag];
	}

	if (PassiveItemStatsDatas.Contains(GameplayTag))
	{
		return PassiveItemStatsDatas[GameplayTag];
	}
	return nullptr;
}

void UDiaGameInstance::Init()
{
	UE_LOG(LogDia, Display, TEXT(__FUNCTION__));

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		UE_LOG(LogDia, Warning, TEXT("Found subsystem %s"), *OnlineSubsystem->GetSubsystemName().ToString());
		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogDia, Warning, TEXT("Found SessionInterface"));
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UDiaGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UDiaGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UDiaGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UDiaGameInstance::OnJoinSessionComplete);
		}
	}

	Super::Init();
}

void UDiaGameInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UDiaGameInstance, CurrentSelectedCharacterInfo);
}

void UDiaGameInstance::Host(FString ServerName)
{
	if (!SessionInterface.IsValid()) return;
	DesiredServerName = ServerName;
	FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
	if (ExistingSession == nullptr)
	{
		CreateSession();
	}
	else
	{
		SessionInterface->DestroySession(SESSION_NAME);
	}
}

void UDiaGameInstance::Join(int32 Index)
{
	if (!SessionInterface.IsValid() || !SessionSearch.IsValid()) return;

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
}

void UDiaGameInstance::FindSession()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		ServerDatas.Empty();

		//SessionSearch->bIsLanQuery = true;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionSearch->MaxSearchResults = 100;

		UE_LOG(LogTemp, Warning, TEXT("Starting find session."));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UDiaGameInstance::CreateSession()
{
	if (!SessionInterface.IsValid()) return;

	FOnlineSessionSettings SessionSettings;
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem->GetSubsystemName() == "NULL")
	{
		SessionSettings.bIsLANMatch = true; // 로컬도 진행
	}
	else
	{
		SessionSettings.bIsLANMatch = false;
	}

	SessionSettings.NumPublicConnections = 5; // 접속자 수
	SessionSettings.bShouldAdvertise = true; // 공개방 설정
	SessionSettings.bUsesPresence = true; // Presence 활성화

	SessionSettings.Set(SERVER_NAME_SETTINGS_KEY, DesiredServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	SessionSettings.bUseLobbiesIfAvailable = true;

	SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
}

void UDiaGameInstance::StartSession()
{
	if (!SessionInterface.IsValid()) return;
	SessionInterface->StartSession(SESSION_NAME);
}

void UDiaGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success) return;
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete. %s"), *SessionName.ToString());

	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, TEXT("Hosting"));

	// 선택된 Stage가 있다면 ServerTravel
	if (CurrentSelectedStageInfo && !CurrentSelectedStageInfo->Level.GetLongPackageName().IsEmpty())
	{
		FString URL = CurrentSelectedStageInfo->Level.GetLongPackageName();
		UWorld* World = GetWorld();

		World->ServerTravel(URL.Append("?listen"));

		APlayerController* PlayerController = World->GetFirstPlayerController();
		FInputModeGameOnly InputModeData;
		PlayerController->SetInputMode(InputModeData);
	}
}

void UDiaGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (!Success) return;
	UE_LOG(LogDia, Warning, TEXT("OnDestroySessionComplete. %s"), *SessionName.ToString());
	CreateSession();
}

void UDiaGameInstance::OnFindSessionsComplete(bool Success)
{
	if (!Success) return;
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete. count: %d"), SessionSearch->SearchResults.Num());

	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Find Sessions..")));
	for (const FOnlineSessionSearchResult& Result : SessionSearch->SearchResults)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found session name: %s"), *Result.GetSessionIdStr());
		FServerData Data;
		FString ServerName;
		if (Result.Session.SessionSettings.Get(SERVER_NAME_SETTINGS_KEY, ServerName))
		{
			Data.Name = ServerName;
		}
		else
		{
			Data.Name = "Could not find name.";
		}

		Data.HostUserName = Result.Session.OwningUserName;
		Data.MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;
		Data.NumOfPlayers = Data.MaxPlayers - Result.Session.NumOpenPublicConnections;

		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Name: %s, Host: %s, MaxPlayers: %d, NumOfPlayers: %d"), *Data.Name, *Data.HostUserName, Data.MaxPlayers, Data.NumOfPlayers));
		ServerDatas.Add(Data);
	}
	FindSessionsCompleteDelegate.Broadcast();
}

void UDiaGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid()) return;
	// switch (Result)
	// {
	// case EOnJoinSessionCompleteResult::Success:
	// 	JoinSession(SessionName);
	// 	break;
	// default: ;
	// // 다른 실패 케이스
	// // case EOnJoinSessionCompleteResult::SessionIsFull:
	// // case EOnJoinSessionCompleteResult::SessionDoesNotExist:
	// // case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
	// // case EOnJoinSessionCompleteResult::AlreadyInSession:
	// // case EOnJoinSessionCompleteResult::UnknownError:
	// // 	break;
	// }

	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SESSION_NAME, Address))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect string."));
		return;
	}

	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
	UWorld* World = GetWorld();
	APlayerController* PlayerController = World->GetFirstPlayerController();
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	
	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
}
