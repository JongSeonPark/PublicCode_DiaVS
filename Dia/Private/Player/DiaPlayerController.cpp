#include "Player/DiaPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/DiaAbilitySystemComponent.h"
#include "Dia/Dia.h"
#include "Engine/LocalPlayer.h"
#include "Input/DiaInputConfig.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "DiaMathLibrary.h"
#include "NavigationSystem.h"
#include "Character/DiaPlayerCharacter.h"
#include "Game/DiaGameInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/PlayerStart.h"
#include "Interaction/DiaPickable.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Navigation/PathFollowingComponent.h"

ADiaPlayerController::ADiaPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;

	PathFollowingComponent = CreateDefaultSubobject<UPathFollowingComponent>("PathFollowingComponent");
	if (PathFollowingComponent)
	{
		PathFollowingComponent->OnRequestFinished.AddUObject(this, &ADiaPlayerController::OnMoveCompleted);
	}
}

void ADiaPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ADiaPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	DiaAbilitySystemComponent = Cast<UDiaAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InPawn));
	PathFollowingComponent->Initialize();
}

void ADiaPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	DiaAbilitySystemComponent = nullptr;
	PathFollowingComponent->Cleanup();
}

void ADiaPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	PathFollowingComponent->Initialize();
}

void ADiaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent) return;
	
	// 키보드를 통한 Movement 설정
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADiaPlayerController::OnMoveTriggerd);

	// Active Ability 설정
	if (InputConfig)
	{
		for (const FDiaInputAction InputData : InputConfig->InputActions)
		{
			if (InputData.InputTag.IsValid() && InputData.InputAction->IsValidLowLevel())
			{
				EnhancedInputComponent->BindAction(InputData.InputAction, ETriggerEvent::Started, this, &ADiaPlayerController::OnAbilityKeyPressed, InputData.InputTag);
				EnhancedInputComponent->BindAction(InputData.InputAction, ETriggerEvent::Completed, this, &ADiaPlayerController::OnAbilityKeyReleased, InputData.InputTag);
				EnhancedInputComponent->BindAction(InputData.InputAction, ETriggerEvent::Triggered, this, &ADiaPlayerController::OnAbilityKeyHeld, InputData.InputTag);
			}
		}
	}
	EnhancedInputComponent->BindAction(ConfirmTargetAction, ETriggerEvent::Completed, this, &ADiaPlayerController::OnTargetConfirm);
	EnhancedInputComponent->BindAction(CancelTargetAction, ETriggerEvent::Completed, this, &ADiaPlayerController::OnTargetCancel);
}

void ADiaPlayerController::OnMoveTriggerd(const FInputActionValue& InputActionValue)
{
	if (PathFollowingComponent->GetStatus() != EPathFollowingStatus::Idle)
		PathFollowingComponent->RequestMoveWithImmediateFinish(EPathFollowingResult::Aborted);

	const FVector2D Value = InputActionValue.Get<FVector2D>();
	
	UPawnMovementComponent* MovementComponent = GetPawn()->GetMovementComponent();
	MovementComponent->AddInputVector(FVector(Value.Y, Value.X, 0) * 1000.f);
}

void ADiaPlayerController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (Result.Code == EPathFollowingResult::Success && PickableItem.IsValid())
	{
		if (PickableItem->Implements<UDiaPickable>())
		{
			PickItem_Server(PickableItem.Get());
			PickableItem.Reset();
		}
	}
}

void ADiaPlayerController::OnAbilityKeyPressed(FGameplayTag InputTag)
{
	if (DiaAbilitySystemComponent)
	{
		for (FGameplayAbilitySpec& AbilitySpec : DiaAbilitySystemComponent->GetActivatableAbilities())
		{
			if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				if (!AbilitySpec.IsActive())
				{
					DiaAbilitySystemComponent->TryActivateAbility(AbilitySpec.Handle);
				}
			}
		}
	}
}

void ADiaPlayerController::OnAbilityKeyReleased(FGameplayTag InputTag)
{
	if (DiaAbilitySystemComponent)
	{
		for (FGameplayAbilitySpec& AbilitySpec : DiaAbilitySystemComponent->GetActivatableAbilities())
		{
			if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				DiaAbilitySystemComponent->AbilitySpecInputReleased(AbilitySpec);
			}
		}
	}
}

void ADiaPlayerController::OnAbilityKeyHeld(FGameplayTag InputTag)
{
	if (DiaAbilitySystemComponent)
	{
		for (FGameplayAbilitySpec& AbilitySpec : DiaAbilitySystemComponent->GetActivatableAbilities())
		{
			if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				DiaAbilitySystemComponent->AbilitySpecInputPressed(AbilitySpec);
			}
		}
	}
}

void ADiaPlayerController::OnTargetConfirm()
{
	if (DiaAbilitySystemComponent)
		DiaAbilitySystemComponent->TargetConfirm();
}

void ADiaPlayerController::OnTargetCancel()
{
	if (DiaAbilitySystemComponent)
		DiaAbilitySystemComponent->TargetCancel();
}

void ADiaPlayerController::DiaSpawnCharacter_Client_Implementation()
{
	if (const UDiaGameInstance* DiaGameInstance = GetGameInstance<UDiaGameInstance>())
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("DiaGameInstance->GetName(): %s"), *DiaGameInstance->GetName()), true, true, FColor::Black, 10);
		auto CurrentSelectedCharacterInfo = DiaGameInstance->GetCurrentSelectedCharacterInfo();
		if (CurrentSelectedCharacterInfo && CurrentSelectedCharacterInfo->CharacterClass)
			SpawnCharacter_Server(CurrentSelectedCharacterInfo->CharacterClass);
	}
}

void ADiaPlayerController::SpawnCharacter_Server_Implementation(TSubclassOf<ADiaPlayerCharacter> CharacterClass)
{
	if (CharacterClass)
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), OutActors);
		FTransform SpawnTransform;

		if (OutActors.Num() > 0)
		{
			const UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
			UDiaMathLibrary::ShuffleArray(OutActors);
			SpawnTransform = OutActors[0]->GetTransform();
		}

		ADiaPlayerCharacter* DiaPlayerCharacter = GetWorld()->SpawnActorDeferred<ADiaPlayerCharacter>(
			CharacterClass,
			SpawnTransform,
			this,
			nullptr,
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
		);

		if (DiaPlayerCharacter)
		{
			UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Possess")), true, true, FColor::Black, 10);
			Possess(DiaPlayerCharacter);
			DiaPlayerCharacter->FinishSpawning(SpawnTransform);
		}
	}
}

void ADiaPlayerController::TryPickItem(AActor* InPickableItem)
{
	UAIBlueprintHelperLibrary::SimpleMoveToActor(this, InPickableItem);
	PickableItem = InPickableItem;
}

void ADiaPlayerController::PickItem_Server_Implementation(AActor* InPickableItem)
{
	IDiaPickable::Execute_Pick(InPickableItem);
}

