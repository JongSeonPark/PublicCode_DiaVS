#include "Game/DiaGameMode.h"

#include "Character/DiaPlayerCharacter.h"
#include "Data/DiaGameModeData.h"
#include "Dia/Dia.h"
#include "Game/DiaGameSession.h"
#include "Game/DiaGameSpawner.h"
#include "Game/DiaGameState.h"
#include "Player/DiaPlayerController.h"
#include "Player/DiaPlayerState.h"
#include "UI/HUD/DiaHUD.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DiaGameplayTags.h"
#include "Game/DiaGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

ADiaGameMode::ADiaGameMode()
{
	if (HasAuthority())
		DiaGameSpawner = CreateDefaultSubobject<UDiaGameSpawner>("DiaSpawnManager");

	DefaultPawnClass = ADiaPlayerCharacter::StaticClass();
	HUDClass = ADiaHUD::StaticClass();
	PlayerControllerClass = ADiaPlayerController::StaticClass();
	GameStateClass = ADiaGameState::StaticClass();
	PlayerStateClass = ADiaPlayerState::StaticClass();
	GameSessionClass = ADiaGameSession::StaticClass();
}

void ADiaGameMode::BeginPlay()
{
	Super::BeginPlay();
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	ListenerHandles.Add(MessageSubsystem.RegisterListener(DiaGameplayTags::Event_DamageNumber, this, &ThisClass::OnDamageNumberMessage));
}

void ADiaGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	for (const FGameplayMessageListenerHandle& Handle : ListenerHandles)
	{
		MessageSubsystem.UnregisterListener(Handle);
	}
	ListenerHandles.Empty();
}

void ADiaGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (DiaGameSpawner)
		DiaGameSpawner->WaveUpdate(DeltaSeconds);
}

void ADiaGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	if (ADiaPlayerController* DiaPlayerController = Cast<ADiaPlayerController>(NewPlayer))
	{
		DiaPlayerController->DiaSpawnCharacter_Client();
	}
}

void ADiaGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	DiaGameSpawner = NewObject<UDiaGameSpawner>(GetWorld());
}

void ADiaGameMode::StartPlay()
{
	Super::StartPlay();
	ADiaGameState* DiaGameState = GetGameState<ADiaGameState>();
	if (!DiaGameState || !DiaGameSpawner || !DiaGameModeData)
	{
		return;
	}

	DiaGameState->SetStartTimeSeconds(DiaGameState->GetServerWorldTimeSeconds());
	DiaGameSpawner->SetDiaGameState(DiaGameState);
	DiaGameSpawner->SetEnemySpawnDatas(DiaGameModeData->EnemySpawnDatas);
}

void ADiaGameMode::OnDamageNumberMessage(FGameplayTag Channel, const FDamageNumberInfo& Payload)
{
	for (TObjectPtr<APlayerState> PlayerState : GameState->PlayerArray)
	{
		if (ADiaPlayerState* DiaPlayerState = Cast<ADiaPlayerState>(PlayerState))
		{
			DiaPlayerState->OnDamageNumberMessage_Client(Payload.Target, Payload.Damage);
		}
	}
}
