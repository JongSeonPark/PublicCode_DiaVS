#include "Character/DiaPlayerCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/DiaAbilitySystemComponent.h"
#include "AbilitySystem/DiaAttributeSet.h"
#include "AbilitySystem/Abilities/DiaGameplayAbility.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Data/DiaCharacterData.h"
#include "Dia/Dia.h"
#include "Game/DiaGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DiaPlayerController.h"
#include "Player/DiaPlayerState.h"
#include "UI/HUD/DiaHUD.h"

ADiaPlayerCharacter::ADiaPlayerCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	GemMagnetSphereComponent = CreateDefaultSubobject<USphereComponent>("GemMagnet");
	GemMagnetSphereComponent->SetCollisionObjectType(ECC_Magnet);
	GemMagnetSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GemMagnetSphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	GemMagnetSphereComponent->SetCollisionResponseToChannel(ECC_Item, ECR_Overlap);
	GemMagnetSphereComponent->SetupAttachment(RootComponent);

	PlayerLookAreaComponent = CreateDefaultSubobject<UBoxComponent>("PlayerLookArea");
	PlayerLookAreaComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PlayerLookAreaComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	PlayerLookAreaComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PlayerLookAreaComponent->SetupAttachment(RootComponent);
	HpBarWidget->SetVisibility(true);
}

void ADiaPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADiaPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilitySystem();
	AddStartupAbilities();
}

void ADiaPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilitySystem();
}

void ADiaPlayerCharacter::ApplyInitialAttributes() const
{
	if (CharacterDefaultReinforceData && PrimaryAttributes)
	{
		FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		ContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(PrimaryAttributes, 0, ContextHandle);

		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_MaxHealth, CharacterDefaultReinforceData->MaxHealth);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_HealthRegeneration, CharacterDefaultReinforceData->HealthRegeneration);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_Armor, CharacterDefaultReinforceData->Armor);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_MoveSpeed, CharacterDefaultReinforceData->MoveSpeed);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_Might, CharacterDefaultReinforceData->Might);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_Speed, CharacterDefaultReinforceData->Speed);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_Duration, CharacterDefaultReinforceData->Duration);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_Area, CharacterDefaultReinforceData->Area);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_Cooldown, CharacterDefaultReinforceData->Cooldown);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_Amount, CharacterDefaultReinforceData->Amount);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_Revival, CharacterDefaultReinforceData->Revival);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_Magnet, CharacterDefaultReinforceData->Magnet);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_Luck, CharacterDefaultReinforceData->Luck);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_Growth, CharacterDefaultReinforceData->Growth);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_Greed, CharacterDefaultReinforceData->Greed);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DiaGameplayTags::Attribute_Primary_Curse, CharacterDefaultReinforceData->Curse);

		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
	ApplyGameplayEffectToSelf(HealthRegenerationGameplayEffectClass);
	Super::ApplyInitialAttributes();
}

void ADiaPlayerCharacter::InitAbilitySystem()
{
	ADiaPlayerState* DiaPlayerState = GetPlayerState<ADiaPlayerState>();

	// false면 중지 어서트
	check(DiaPlayerState);
	AbilitySystemComponent = CastChecked<UDiaAbilitySystemComponent>(DiaPlayerState->GetAbilitySystemComponent());
	AttributeSet = CastChecked<UDiaAttributeSet>(DiaPlayerState->GetAttributeSet());
	AbilitySystemComponent->InitAbilityActorInfo(DiaPlayerState, this);
	
	if (ADiaPlayerController* DiaPlayerController = Cast<ADiaPlayerController>(GetController()))
	{
		if (ADiaHUD* DiaHUD = DiaPlayerController->GetHUD<ADiaHUD>())
		{
			DiaHUD->InitOverlay(DiaPlayerController, DiaPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	
	// 기존 값으로 Base값 설정
	BaseSpeed = GetCharacterMovement()->MaxWalkSpeed;
	BaseMagnetRadius = GemMagnetSphereComponent->GetUnscaledSphereRadius();

	// Primary에 의한 MoveSpeed 변경
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UDiaAttributeSet::GetPrimaryMoveSpeedAttribute()).AddLambda(
		[&](const FOnAttributeChangeData& AttributeChangeData)
		{
			GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * (1 + AttributeChangeData.NewValue);
		});

	// Primary에 의한 Magnet 변경
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UDiaAttributeSet::GetPrimaryMagnetAttribute()).AddLambda(
		[&](const FOnAttributeChangeData& AttributeChangeData)
		{
			GemMagnetSphereComponent->SetSphereRadius(BaseMagnetRadius * (1 + AttributeChangeData.NewValue));
		});
	
	ApplyInitialAttributes();
	Super::InitAbilitySystem();
	UpdateHpBarWidgetController();
}

void ADiaPlayerCharacter::AddToExp_Implementation(int32 InExp)
{
	if (ADiaPlayerState* DiaPlayerState = GetPlayerState<ADiaPlayerState>())
		DiaPlayerState->AddExp(InExp);
}

int32 ADiaPlayerCharacter::GetExp_Implementation() const
{
	if (const ADiaPlayerState* DiaPlayerState = GetPlayerState<ADiaPlayerState>())
		return DiaPlayerState->GetExp();
	return 0;
}

void ADiaPlayerCharacter::AddToLevel_Implementation(int32 InLevel)
{
	if (ADiaPlayerState* DiaPlayerState = GetPlayerState<ADiaPlayerState>())
	{
		DiaPlayerState->AddLevel(InLevel);
		DiaPlayerState->AddLevelUpPoint(InLevel);
		OnLevelUp();
	}
}

int32 ADiaPlayerCharacter::FindLevelForExp_Implementation(int32 InExp, int32& RestExp) const
{
	if (ADiaPlayerState* DiaPlayerState = GetPlayerState<ADiaPlayerState>())
	{
		if (IsValid(ExpPerLevelCurveFloat))
		{
			int32 LevelTemp = DiaPlayerState->GetPlayerLevel();

			while (true)
			{
				float LevelExp = ExpPerLevelCurveFloat->GetFloatValue(LevelTemp);
				if (InExp >= LevelExp)
				{
					InExp -= LevelExp;
					LevelTemp++;
				}
				else
				{
					RestExp = InExp;
					return LevelTemp;
				}
			}
		}
	}

	return 0;
}

void ADiaPlayerCharacter::SetExp_Implementation(const int32& InExp)
{
	if (ADiaPlayerState* DiaPlayerState = GetPlayerState<ADiaPlayerState>())
		DiaPlayerState->SetExp(InExp);
}

int32 ADiaPlayerCharacter::GetExpForCurrentLevel_Implementation() const
{
	if (const ADiaPlayerState* DiaPlayerState = GetPlayerState<ADiaPlayerState>())
		if (IsValid(ExpPerLevelCurveFloat))
			return ExpPerLevelCurveFloat->GetFloatValue(DiaPlayerState->GetPlayerLevel());
	return 0;
}

void ADiaPlayerCharacter::Die_Implementation()
{
	Super::Die_Implementation();
	AbilitySystemComponent->CancelAllAbilities();
	AbilitySystemComponent->RemoveActiveEffectsWithTags(FGameplayTagContainer(DiaGameplayTags::Effect_HealthRegeneration));
	Die_Client();
}

int32 ADiaPlayerCharacter::GetCharacterLevel_Implementation() const
{
	if (const ADiaPlayerState* DiaPlayerState = GetPlayerState<ADiaPlayerState>())
		return DiaPlayerState->GetPlayerLevel();
	return 0;
}

void ADiaPlayerCharacter::Die_Client_Implementation()
{
	if (ADiaPlayerController* DiaPlayerController = Cast<ADiaPlayerController>(GetController()))
		DiaPlayerController->OnCharacterDead.Broadcast();
}

void ADiaPlayerCharacter::AddStartupAbilities()
{
	for (const TSubclassOf<UGameplayAbility> Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);

		if (const UDiaGameplayAbility* DiaAbility = Cast<UDiaGameplayAbility>(AbilitySpec.Ability))
		{
			if (DiaAbility->StartupInputTag.IsValid())
				AbilitySpec.DynamicAbilityTags.AddTag(DiaAbility->StartupInputTag);
		}
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}

	// 기본 무기 추가
	UDiaGameInstance* DiaGameInstance = GetGameInstance<UDiaGameInstance>();
	if (DiaGameInstance && CharacterDefaultReinforceData && CharacterDefaultReinforceData->WeaponTag.IsValid())
	{
		TObjectPtr<UWeaponStats> WeaponStats = DiaGameInstance->GetWeaponStatsDatas()[CharacterDefaultReinforceData->WeaponTag];
		if (WeaponStats && WeaponStats->GameplayAbilityClass)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(WeaponStats->GameplayAbilityClass, 1);
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}

void ADiaPlayerCharacter::OnLevelUp_Implementation()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		this,
		Niagara_LevelUp, GetActorLocation(),
		FRotator::ZeroRotator,
		FVector(1.f, 1.f, 1.f),
		true,
		true,
		ENCPoolMethod::None,
		true);

	UGameplayStatics::PlaySound2D(GetWorld(), LevelUpSound);
}
